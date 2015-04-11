//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/VisualTree.hpp"
#include "../core/State.hpp"
#include "../core/MetadataInfo.hpp"
#include "../core/VisualColourMap.hpp"
#include "../core/NodePhylo.hpp"
#include "../core/Filter.hpp"

#include "../glUtils/ErrorGL.hpp"
#include "../glUtils/Font.hpp"

#include "../gui/PygmyFrame.hpp"

#include "../utils/Tree.hpp"
#include "../utils/Geometry.hpp"
#include "../utils/StringTools.hpp"

#include "../utils/ColourMap.hpp"
#include "../utils/ColourMapDiscrete.hpp"
#include "../utils/ColourMapContinuous.hpp"
#include "../utils/Point.hpp"

#include "../utils/ParsimonyCalculator.hpp"

using namespace pygmy;
using namespace utils;

VisualTree::VisualTree(utils::Tree<NodePhylo>::Ptr tree)
	: m_originalTree(tree), m_activeNode(VisualNode(VisualMarker(), NULL)), m_colourMapSpacing(10), m_branchStyle(CLADOGRAM_BRANCHES)
{	
	m_tree = m_originalTree->Clone();

	// reserve maximum required memory for visible elements
	m_visibleBranches.reserve(m_tree->GetNumberOfNodes()*2);
	m_visibleNodes.reserve(m_tree->GetNumberOfNodes());
	m_visibleLeafNodes.reserve(m_tree->GetNumberOfLeaves());
}

void VisualTree::LayoutBranchStyle()
{
	// set x-position of all nodes
	std::queue<NodePhylo*> queue;
	queue.push(m_tree->GetRootNode());

	while(!queue.empty())
	{
		NodePhylo* curNode = queue.front();
		queue.pop();

		if(m_branchStyle == PHYLOGRAM_BRANCHES)
			curNode->SetXPos(curNode->GetDistanceToRoot() / m_tree->GetLengthOfTree());
		else if(m_branchStyle == EQUAL_BRANCHES)
			curNode->SetXPos(float(curNode->GetDepth()) / m_tree->GetRootNode()->GetHeight());
		else if(m_branchStyle == CLADOGRAM_BRANCHES)
			curNode->SetXPos(1.0f - float(curNode->GetHeight()) / m_tree->GetRootNode()->GetHeight());

		for(uint i = 0; i < curNode->GetNumberOfChildren(); ++i)
			queue.push(curNode->GetChild(i));		
	}
}

void VisualTree::LayoutY()
{
	// set y-position of nodes via a post-order traversal
	uint yLeafPosition = 0;
	LayoutY(m_tree->GetRootNode(), yLeafPosition);

	// normalize to unit length and set mock intervals
	std::queue<NodePhylo*> queue;
	queue.push(m_tree->GetRootNode());

	while(!queue.empty())
	{
		NodePhylo* curNode = queue.front();
		queue.pop();

		curNode->SetYPos(curNode->GetYPos() / m_tree->GetNumberOfLeaves());

		Interval interval = curNode->GetInterval();
		curNode->SetInterval(Interval(interval.start / m_tree->GetNumberOfLeaves(), 
																		interval.end / m_tree->GetNumberOfLeaves()));

		for(uint i = 0; i < curNode->GetNumberOfChildren(); ++i)
			queue.push(curNode->GetChild(i));		
	}
}

void VisualTree::LayoutY(NodePhylo* node, uint& yLeafPosition)
{
	if(!node->IsLeaf())
	{
		float minY = FLT_MAX;
		float maxY = 0.0f;

		float startInterval = FLT_MAX;
		float endInterval = 0.0f;

		for(uint i = 0; i < node->GetNumberOfChildren(); ++i)
		{
			if(node->GetChild(i)->IsLeaf())
			{
				node->GetChild(i)->SetInterval(Interval(yLeafPosition, yLeafPosition));
				node->GetChild(i)->SetYPos(yLeafPosition);
				yLeafPosition++;
			}

			LayoutY(node->GetChild(i), yLeafPosition);

			float yPos = node->GetChild(i)->GetYPos();
			if(yPos < minY)
				minY = yPos;

			if(yPos > maxY)
				maxY = yPos;

			Interval interval = node->GetChild(i)->GetInterval();

			if(interval.start < startInterval)
				startInterval = interval.start;

			if(interval.end > endInterval)
				endInterval = interval.end;
		}

		node->SetInterval(Interval(startInterval, endInterval));
		node->SetYPos(minY + 0.5*(maxY-minY));
	}
}

void VisualTree::CalculateTreeDimensions(uint width, uint height, float zoom)
{
	// calculate tree height such that labels are as close together as possible without overlapping
	Point border = State::Inst().GetBorderSize();
	m_treeHeight = m_tree->GetNumberOfLeaves()*m_highestLabel;

	// if there are no labels, than ensure branches do not overlap
	if(!State::Inst().GetShowLeafLabels() && !State::Inst().GetShowMetadataLabels())
		m_treeHeight = m_tree->GetNumberOfLeaves();

	// set width of tree so colour map and labels have enough room
	m_treeWidth = width - m_widestLabel - 2*border.x;
	if(m_visualColourMap)
		m_treeWidth -= (m_visualColourMap->GetWidth() + m_colourMapSpacing);

	m_viewportHeightFrac = height / (m_treeHeight * zoom);
	if(m_viewportHeightFrac > 1.0f)
		m_viewportHeightFrac = 1.0f;
}

void VisualTree::Render(int width, int height, float translation, float zoom)
{
	glUtils::ErrorGL::Check();

	CalculateTreeDimensions(width, height, zoom);

	// *** Render tree. ***
	RenderTree(translation, zoom);

	// *** Render any label selection heighlights. ***
	RenderTextSearch(translation, zoom);
	
	// *** Render leaf node labels ***
	RenderLeafNodeLabels(translation, zoom);

	//** Render internal node labels ***
	RenderInternalLabels(translation, zoom);

	// *** Render the active node. ***
	RenderActiveNode(translation, zoom);

	glUtils::ErrorGL::Check();
}

void VisualTree::RenderTree(float translation, float zoom)
{
	glUtils::ErrorGL::Check();

	// Get size of border (in pixels)
	Point border = State::Inst().GetBorderSize();

	glPushMatrix();
	{
		glDisable(GL_LINE_SMOOTH);

		int thicknessMajor = int((1 + State::Inst().GetLineWidth())*0.5);
		int thicknessMinor = int(State::Inst().GetLineWidth()*0.5);
		int pointSize = State::Inst().GetLineWidth()+4;

		// scale factor for tree (Note: glScalef() is not used as we want lines to be pixel aligned)
		float sx = m_treeWidth;
		float sy = m_treeHeight * zoom;

		// translation factor for tree (Note: glTranslatef() is not used as we want lines to be pixel aligned)
		int dx = border.x;
		int dy = int(border.y - translation + 0.5);

		float viewportMin = (translation - border.y) / (m_treeHeight * zoom);
		if(viewportMin < 0.0f)	// can be negative before we have translated past the border
			viewportMin = 0.0f;

		float viewportMax = viewportMin + m_viewportHeightFrac;

		// Keep track of all visible elements
		m_visibleBranches.clear();
		m_visibleLeafNodes.clear();
		m_visibleNodes.clear();

		// Render tree in breadth-first search order. A branch and bound algorithm is used
		// to render only those elements (nodes and edges) contained within the current viewport.
		// Specifically, if the y interval extents covered by the children of a given node are
		// all outside the viewport there is no need to render the current node and none of its
		// children need to be considered.
		std::queue<NodePhylo*> queue;
		queue.push(m_tree->GetRootNode());

		while(!queue.empty())
		{
			NodePhylo* curNode = queue.front();
			Point curNodePos = curNode->GetPosition();

			int curNodeX = int(curNodePos.x*sx + dx + 0.5);
			int curNodeY = int(curNodePos.y*sy + dy + 0.5);

			VisualMarker visualMarker(curNode->GetColour(), pointSize, VisualMarker::CIRCLE, VisualMarker::FILL, Point(curNodeX, curNodeY));
			visualMarker.SetVisibility(curNode->IsSelected());
			visualMarker.SetSelected(curNode->IsSelected());

			float yMin = 1000.0f, yMax = 0.0f;
			std::vector<NodePhylo*> children = curNode->GetChildren();
			foreach(NodePhylo* child, children)
			{	
				Point childPos = child->GetPosition();

				int childNodeX = int(childPos.x*sx + dx + 0.5);
				int childNodeY = int(childPos.y*sy + dy + 0.5);

				// check if child node need to be rendered
				if(child->GetInterval().start <= viewportMax && child->GetInterval().end >= viewportMin)
					queue.push(child);

				// Draw branches from parent to child node	
				Rect rect;

				// draw horizontal line
				rect.ll = Point(curNodeX, int(childNodeY  + thicknessMajor));
				rect.ul = Point(curNodeX, int(childNodeY - thicknessMinor));
				rect.ur = Point(childNodeX, int(childNodeY - thicknessMinor));
				rect.lr = Point(childNodeX, int(childNodeY + thicknessMajor));

				if(yMin > childPos.y) 
					yMin = childPos.y;

				if(yMax < childPos.y) 
					yMax = childPos.y;

				VisualRect::RECT_TYPE type = VisualRect::HORIZONTAL;
				VisualRect visualRect(curNode->GetColour(), child->GetColour(), rect, type);
				visualRect.Render();

				m_visibleBranches.push_back(VisualBranch(visualRect, child));
			}

			// It is better to draw a single vertical line as this reduces the number of line segments
			// that must be rendered and ensures that only a single crisp line is drawn (as opposed to multiple
			// overlapping lines which can cause strange visual artifacts).

			// Draw vertical line adjusting for the width of the line being drawn. For some reason, the offset
			// needed to account for the line width is different for the start and end of the line (???).
			if(!curNode->IsLeaf())
			{
				Rect top;
				top.ll = Point(int(curNodeX + thicknessMajor), int(curNodeY - thicknessMinor));
				top.ul = Point(int(curNodeX - thicknessMinor), int(curNodeY - thicknessMinor));
				top.ur = Point(int(curNodeX - thicknessMinor), int(yMax*sy + dy + thicknessMajor + 0.5));
				top.lr = Point(int(curNodeX + thicknessMajor), int(yMax*sy + dy + thicknessMajor + 0.5));

				VisualRect topVisualRect(curNode->GetColour(), curNode->GetColour(), top, VisualRect::VERTICAL);
				topVisualRect.Render();
				m_visibleBranches.push_back(VisualBranch(topVisualRect, curNode));

				Rect bottom;
				bottom.ll = Point(int(curNodeX + thicknessMajor), int(yMin*sy + dy - thicknessMinor + 0.5));
				bottom.ul = Point(int(curNodeX - thicknessMinor), int(yMin*sy + dy - thicknessMinor + 0.5));
				bottom.ur = Point(int(curNodeX - thicknessMinor), int(curNodeY + thicknessMajor));
				bottom.lr = Point(int(curNodeX + thicknessMajor), int(curNodeY + thicknessMajor));

				VisualRect bottomVisualRect(curNode->GetColour(), curNode->GetColour(), bottom, VisualRect::VERTICAL);
				bottomVisualRect.Render();
				m_visibleBranches.push_back(VisualBranch(bottomVisualRect, curNode));
			}
	
			// Check if the current node is within the viewport. We only need to render this
			// node and check for mouse events occuring on this node if it is within the viewport.
			// Note that a node not being within the viewport does not imply that none of its children
			// are within the viewport.
			if(curNodePos.y <= viewportMax && curNodePos.y >= viewportMin)
			{
				// Render node
				visualMarker.Render();

				// Track all visible nodes
				m_visibleNodes.push_back(VisualNode(visualMarker, curNode));

				// Track visible leaf nodes
				if(curNode->IsLeaf())
					m_visibleLeafNodes.push_back(curNode);
			}

			// Remove current parent node
			queue.pop();
		}	

		glEnable(GL_LINE_SMOOTH);
	}
	glPopMatrix();

	glUtils::ErrorGL::Check();
}

void VisualTree::RenderTextSearch(float translation, float zoom)
{
	glUtils::ErrorGL::Check();

	// Get size of border (in pixels)
	Point border = State::Inst().GetBorderSize();

	// *** Render any label selection heighlights. ***
	glPushMatrix();
	{
		glTranslatef(border.x, border.y - translation, 0.0f);

		float height = (float)State::Inst().GetFont()->GetSize();
		float descender = (float)State::Inst().GetFont()->GetDescender();

		foreach(NodePhylo* leaf, m_visibleLeafNodes)
		{
			Point childPos = leaf->GetPosition();

			// calculate position of label
			BBox bbox = m_bboxMap[leaf->GetId()];
			
			float fontY = childPos.y * m_treeHeight * zoom - 0.2f * (height-descender);	
			float fontX = childPos.x * m_treeWidth + State::Inst().GetLabelOffset();

			// render bounding box for label
			if(m_searchFilter->Filtered(leaf->GetId()))
			{
				Colour colour = m_searchFilter->GetColour();
				glColor4f(colour.GetRed(), colour.GetGreen(), colour.GetBlue(), colour.GetAlpha());

				glBegin(GL_QUADS);
					glVertex2f(bbox.x + fontX - 2, bbox.y + fontY - 2);
					glVertex2f(bbox.dx + fontX + 1, bbox.y + fontY - 2);
					glVertex2f(bbox.dx + fontX + 1, bbox.dy + fontY + 2);
					glVertex2f(bbox.x + fontX - 2, bbox.dy + fontY + 2);
				glEnd();	
			}
		}
	}
	glPopMatrix();

	glUtils::ErrorGL::Check();
}

void VisualTree::RenderLeafNodeLabels(float translation, float zoom)
{
	glUtils::ErrorGL::Check();

	if(!State::Inst().GetShowLeafLabels() && !State::Inst().GetShowMetadataLabels())
		return;

	// Get size of border (in pixels)
	Point border = State::Inst().GetBorderSize();

	State::Inst().GetFont()->SetSize(State::Inst().GetTreeFontSize());

	glPushMatrix();
	{
		Colour colour = State::Inst().GetTreeFontColour();
		glColor3f(colour.GetRed(), colour.GetGreen(), colour.GetBlue());

		float height = (float)State::Inst().GetFont()->GetSize();
		float descender = (float)State::Inst().GetFont()->GetDescender();

		foreach(NodePhylo* leaf, m_visibleLeafNodes)
		{
			// adjust position of nodes based on desired orientation
			Point childPos = leaf->GetPosition();

			int fontY = int(border.y + childPos.y * m_treeHeight * zoom - 0.2f * (height-descender) + 0.5);	
			int fontX = int(border.x + childPos.x * m_treeWidth + State::Inst().GetLabelOffset() + 0.5);

			// render label		
			if(State::Inst().GetShowLeafLabels() && State::Inst().GetShowMetadataLabels())
			{
				std::wstring label = leaf->GetName() + _T(" [") + leaf->GetData(State::Inst().GetMetadataField()) + _T("]");
				State::Inst().GetFont()->Render(label, fontX, int(fontY - translation + 0.5));	
			}
			else if(State::Inst().GetShowLeafLabels())
			{
				State::Inst().GetFont()->Render(leaf->GetName(), fontX, int(fontY - translation + 0.5));
			}
			else if(State::Inst().GetShowMetadataLabels())
			{
				State::Inst().GetFont()->Render(leaf->GetData(State::Inst().GetMetadataField()), fontX, int(fontY - translation + 0.5));
			}
		}
	}
	glPopMatrix();

	glUtils::ErrorGL::Check();
}

void VisualTree::RenderInternalLabels(float translation, float zoom)
{
	if(!State::Inst().GetShowInternalLabels())
		return;

	glUtils::ErrorGL::Check();

	// Get size of border (in pixels)
	Point border = State::Inst().GetBorderSize();

	State::Inst().GetFont()->SetSize(State::Inst().GetInternalNodeFontSize());

	glUtils::ErrorGL::Check();

	glPushMatrix();
	{
		Colour colour = State::Inst().GetInternalNodeFontColour();
		glColor3f(colour.GetRed(), colour.GetGreen(), colour.GetBlue());

		float height = (float)State::Inst().GetFont()->GetSize();
		float descender = (float)State::Inst().GetFont()->GetDescender();

		foreach(VisualNode& visNode, m_visibleNodes)
		{
			NodePhylo* node = visNode.node;
			if(node->IsLeaf() && State::Inst().GetInternalNodeField() != _T("Distance"))
				continue;

			// set position of label
			Point pos = node->GetPosition();

			std::wstring label;
			if(State::Inst().GetInternalNodeField() == _T("Bootstrap"))
			{
				label = _T("N/A");
				if(node->GetBootstrapToParent() != Node::NO_DISTANCE)
				{
					label = utils::StringTools::ToString(node->GetBootstrapToParent(), 
																									State::Inst().GetInternalNodeFontPrecision(), 
																									State::Inst().GetInternalNodeFontScientific());
				}
			}
			else if(State::Inst().GetInternalNodeField() == _T("Distance"))
			{
				label = _T("N/A");
				if(node->GetDistanceToParent() != Node::NO_DISTANCE)
				{
					label = utils::StringTools::ToString(node->GetDistanceToParent(), 
																								State::Inst().GetInternalNodeFontPrecision(), 
																								State::Inst().GetInternalNodeFontScientific());
				}
			}
			else if(State::Inst().GetInternalNodeField() == _T("Height"))
			{
				label = utils::StringTools::ToString(TreeTools<NodePhylo>::GetDepth(node));
			}
			else if(State::Inst().GetInternalNodeField() == _T("Name"))
			{
				label = node->GetName();
			}
			else if(State::Inst().GetInternalNodeField() == _T("Number of Leaves"))
			{
				label = utils::StringTools::ToString(TreeTools<NodePhylo>::GetNumberOfLeaves(node));
			}
			else if(State::Inst().GetInternalNodeField() == _T("Parsimony Data"))
			{
				label = _T("N/A");
				if(m_parsimonyCalculator)
				{
					ParsimonyData data;
					m_parsimonyCalculator->GetData(node, data);

					label = utils::StringTools::ToString(data.nodeScore) + _T(": ");

					std::map<std::wstring, uint>::iterator it;
					for ( it=data.characterScores.begin() ; it != data.characterScores.end(); it++ )
					{
						label += it->first + _T("(") + utils::StringTools::ToString(it->second) + _T("), ");
					}

					label = label.substr(0, label.length()-2);
					label += _T(" : ");

					std::set<std::wstring>::iterator itSet;
					for(itSet=data.parsimoniousCharacters.begin(); itSet != data.parsimoniousCharacters.end(); itSet++)
					{
						label += (*itSet) + _T(",");
					}

					label = label.substr(0,label.length()-1);
				}
			}

			if(utils::StringTools::IsIntegerNumber(label))
			{
				label = label.substr(0, label.find(_T(".")));
			}

			BBox bb = State::Inst().GetFont()->GetBoundingBox(label);
			int fontY, fontX;
			if(State::Inst().GetInternalLabelPos() == _T("Right"))
			{
				fontY = int(border.y + pos.y * m_treeHeight * zoom  - 0.2f * (height-descender));
				fontX = int(border.x + pos.x * m_treeWidth + State::Inst().GetLineWidth() + 1.5);
			}
			else if(State::Inst().GetInternalLabelPos() == _T("Above Left"))
			{				
				fontY = int(border.y + pos.y * m_treeHeight * zoom - 0.2f * (height-descender) + bb.Height()*0.5 + State::Inst().GetLineWidth() + 0.5);	
				fontX = int(border.x + pos.x * m_treeWidth - bb.Width() - State::Inst().GetLineWidth() + 0.5);
			}

			State::Inst().GetFont()->Render(label, fontX, int(fontY - translation + 0.5));
		}
	}
	glPopMatrix();

	glUtils::ErrorGL::Check();
}

void VisualTree::RenderActiveNode(float translation, float zoom)
{
	/*
	glUtils::ErrorGL::Check();

	if(m_activeNode.node != NULL)
	{
		// Get size of border (in pixels)
		Point border = State::Inst().GetBorderSize();

		glPushMatrix();
		{
			glTranslatef(border.x, border.y - translation, 0.0f);
			glScalef(m_treeWidth, m_treeHeight * zoom, 1.0f);

			Point activePos = m_activeNode.node->GetPosition();

			glLineWidth(State::Inst().GetLineWidth()+2);
			glColor3f(1.0f, 0.48f, 0.14f);

			// highlight all lines going to children nodes
			std::vector<NodePhylo*> children = m_activeNode.node->GetChildren();
			foreach(NodePhylo* child, children)
			{
				Point childPos = child->GetPosition();

				if(m_layout == VisualTree::SLANTED_CLADOGRAM)
				{
					glBegin(GL_LINES); 
						glVertex2f(activePos.x, activePos.y);
						glVertex2f(childPos.x, childPos.y);
					glEnd();
				}
				else
				{
					// highlight just the vertical lines
					glBegin(GL_LINES); 
						glVertex2f(activePos.x, activePos.y);
						glVertex2f(activePos.x, childPos.y);
					glEnd();	
				}
			}

			// highlight line going to parent
			Point parentPos = Point(0.0f, 0.0f);
			if(!m_activeNode.node->IsRoot())
			{
				parentPos = m_activeNode.node->GetParent()->GetPosition();

				if(m_layout == VisualTree::SLANTED_CLADOGRAM)
				{
					glBegin(GL_LINES); 
						glVertex2f(activePos.x, activePos.y);
						glVertex2f(parentPos.x, parentPos.y);
					glEnd();
				}
				else
				{
					// highlight just horizontal line
					glBegin(GL_LINES); 
						glVertex2f(activePos.x, activePos.y);
						glVertex2f(parentPos.x, activePos.y);
					glEnd();	
				}
			}

			// draw subtree bounding box
			glLineWidth(State::Inst().GetLineWidth());
			glColor3f(0.8f, 0.56f, 0.28f);
			float yLabelSpacing = m_highestLabel / m_treeHeight;

			glBegin(GL_LINE_STRIP);
				glVertex2f(parentPos.x, m_activeNode.node->GetInterval().start - 0.5 * yLabelSpacing);
				glVertex2f(parentPos.x, m_activeNode.node->GetInterval().end + 0.5 * yLabelSpacing);
				glVertex2f(1.0f, m_activeNode.node->GetInterval().end + 0.5 * yLabelSpacing);
				glVertex2f(1.0f, m_activeNode.node->GetInterval().start - 0.5 * yLabelSpacing);
				glVertex2f(parentPos.x, m_activeNode.node->GetInterval().start - 0.5 * yLabelSpacing);
			glEnd();
		}
		glPopMatrix();
	}

	glUtils::ErrorGL::Check();
	*/
}

void VisualTree::LabelBoundingBoxes()
{
	if(!State::Inst().GetShowLeafLabels() && !State::Inst().GetShowMetadataLabels())
	{
		m_widestLabel = 0;
		m_highestLabel = 0;
		return;
	}

	typedef std::pair<utils::Node::NodeId, BBox> mapItem;

	m_widestLabel = 0;
	m_bboxMap.clear();

	std::vector<NodePhylo*> leafNodes = m_tree->GetLeaves();
	State::Inst().GetFont()->SetSize(State::Inst().GetTreeFontSize());
	foreach(NodePhylo* leaf, leafNodes)
	{
		std::wstring label;
		if(State::Inst().GetShowLeafLabels() && State::Inst().GetShowMetadataLabels())
			label = leaf->GetName() + _T(" [") + leaf->GetData(State::Inst().GetMetadataField()) + _T("]");
		else if(State::Inst().GetShowLeafLabels())
			label = leaf->GetName();
		else if(State::Inst().GetShowMetadataLabels())
			label = leaf->GetData(State::Inst().GetMetadataField());

		BBox bbox = State::Inst().GetFont()->GetBoundingBox(label);
		mapItem item = mapItem(leaf->GetId(), bbox);

		m_bboxMap.insert(item);

		if(bbox.Width() > m_widestLabel)
			m_widestLabel = bbox.Width();
	}

	// get maximum height of label
	BBox bbox = State::Inst().GetFont()->GetBoundingBox(_T("ABCDEFJHIJKLMNOPQRSTUVWXYZabcdefjhijklmnopqrstuvwxyz123456789!@#$%^&*()-_=+[{]}|;:',<.>/?"));
	m_highestLabel = bbox.Height();
}

void VisualTree::PropagateColours(const std::wstring& field, ColourMapPtr colourMap)
{
	FieldInfo fieldInfo = m_metadataInfo->GetInfo(field);

	if(colourMap->GetType() == ColourMap::CATEGORICAL
			|| (colourMap->GetType() == ColourMap::DISCRETE && fieldInfo.dataType == FieldInfo::CATEGORICAL))
	{
		ColourMapDiscretePtr discreteMap = boost::dynamic_pointer_cast<ColourMapDiscrete>(colourMap);

		std::vector<NodePhylo*> nodes = m_tree->GetLeaves();
		foreach(NodePhylo* node, nodes)
		{
			if(!MetadataInfo::IsMissingData(node->GetData(field)))
			{
				Colour colour;
				discreteMap->GetColour(node->GetData(field), colour);
				node->SetColour(colour);
				node->SetMissingData(false);
			}
			else
			{
				node->SetColour(State::Inst().GetColourMissingData());
				node->SetMissingData(true);
			}
		}

		PropagateLeafNodeColours(false);
	}
	else if(colourMap->GetType() == ColourMap::DISCRETE && fieldInfo.dataType == FieldInfo::NUMERICAL)
	{
		ColourMapDiscretePtr discreteMap = boost::dynamic_pointer_cast<ColourMapDiscrete>(colourMap);

		// determine number of colour bins
		uint bins = fieldInfo.values.size();
		if(discreteMap->GetSize() < bins)
			bins = discreteMap->GetSize();

		// calculate bin boundries
		float dValue = (fieldInfo.maxValue - fieldInfo.minValue) / bins;
		float value = fieldInfo.minValue;
		std::vector<double> binBoundries;
		for(uint i = 0; i < bins+1; ++i)
		{
			binBoundries.push_back(value);
			value += dValue;
		}

		// assign each leaf node to a bin
		std::vector<NodePhylo*> nodes = m_tree->GetLeaves();
		foreach(NodePhylo* node, nodes)
		{
			std::wstring nodeValue = node->GetData(field);
			if(!MetadataInfo::IsMissingData(nodeValue))
			{
				float value = utils::StringTools::ToFloat(nodeValue);
				uint bin = 0;
				foreach(double boundry, binBoundries)
				{
					if(value <= boundry)
						break;

					bin++;
				}

				if(value == fieldInfo.maxValue)
					bin = binBoundries.size()-2;

				node->SetColour(discreteMap->GetColour(bin));
				node->SetMissingData(false);
			}
			else
			{
				node->SetColour(State::Inst().GetColourMissingData());
				node->SetMissingData(true);
			}
		}

		PropagateLeafNodeColours(true);
	}
	else if(colourMap->GetType() == ColourMap::CONTINUOUS)
	{
		ColourMapContinuousPtr continuousMap = boost::dynamic_pointer_cast<ColourMapContinuous>(colourMap);

		std::vector<NodePhylo*> nodes = m_tree->GetLeaves();
		foreach(NodePhylo* node, nodes)
		{
			std::wstring nodeValue = node->GetData(field);
			if(!MetadataInfo::IsMissingData(nodeValue))
			{
				if(utils::StringTools::IsDecimalNumber(nodeValue))
				{
					// handle a numerical field using a continuous colour map
					float value = utils::StringTools::ToFloat(nodeValue);			
					node->SetColour(continuousMap->GetColour(value, fieldInfo.minValue, fieldInfo.maxValue));
				}
				else
				{
					// handle a categorical field using a continuous colour map
					uint pos = 0;
					foreach(const std::wstring& value, fieldInfo.values)
					{
						if(nodeValue == value)
							break;

						pos++;
					}

					node->SetColour(continuousMap->GetColour(pos, 0, fieldInfo.values.size()-1));
				}

				node->SetMissingData(false);
			}
			else
			{
				node->SetColour(State::Inst().GetColourMissingData());
				node->SetMissingData(true);
			}
		}

		PropagateLeafNodeColours(true);
	}
}

void VisualTree::PropagateLeafNodeColours(bool bMixColour)
{
	// mark all internal nodes as unprocessed and leaf nodes as processed
	std::vector<NodePhylo*> nodes = m_tree->GetNodes();
	foreach(NodePhylo* node, nodes)
		node->SetProcessed(node->IsLeaf());

	// queue of nodes that need to be assigned a colour
	std::queue<NodePhylo*> queue;	
	std::vector<NodePhylo*> leafNodes = m_tree->GetLeaves();
	foreach(NodePhylo* leaf, leafNodes)
		queue.push(leaf->GetParent());

	while(!queue.empty())
	{
		NodePhylo* node = queue.front();

		if(node->IsProcessed())
		{
			queue.pop();
			continue;
		}

		std::vector<NodePhylo*> children = node->GetChildren();
		float red = 0, green = 0, blue = 0;
		bool bMultipleColours = false;
		bool bProcessed = true;
		bool bAllLeavesMissingData = true;
		uint numChildrenWithData = 0;
		Colour colour;
		foreach(NodePhylo* child, children)
		{
			if(!child->IsProcessed())
			{
				// put node on back of queue for later processing
				queue.push(node);
				bProcessed = false;
				break;
			}

			if(!State::Inst().GetIgnoreMissingData()
						|| (State::Inst().GetIgnoreMissingData() && !child->IsMissingData()))
			{
				bAllLeavesMissingData = false;
				numChildrenWithData++;

				if(bMixColour)
				{
					red += child->GetColour().GetRed();
					green += child->GetColour().GetGreen();
					blue += child->GetColour().GetBlue();
				}
				else
				{
					if(numChildrenWithData == 1)
					{
						colour = child->GetColour();
					}
					else if(child->GetColour() != colour)
					{
						bMultipleColours = true;
						break;
					}
				}
			}
		}

		if(bProcessed)
		{
			if(bAllLeavesMissingData)
			{
				node->SetColour(State::Inst().GetColourMissingData());
				node->SetMissingData(true);
			}
			else if(bMixColour)
			{
				node->SetColour(Colour(red/numChildrenWithData, green/numChildrenWithData, blue/numChildrenWithData));
				node->SetMissingData(false);
			}
			else
			{
				if(bMultipleColours)
					node->SetColour(State::Inst().GetDefaultTreeColour());
				else
					node->SetColour(colour);
				node->SetMissingData(false);
			}

			if(!node->IsRoot())
				queue.push(node->GetParent());

			node->SetProcessed(true);
		}

		queue.pop();
	}
}

void VisualTree::ProjectTree(std::vector<std::wstring>& names)
{
	//m_tree = m_originalTree->Clone();
	m_tree->ProjectTree(names);
	
	if(m_metadataInfo)
	{
		m_metadataInfo->SetMetadata(m_tree);
		((PygmyFrame*)App::Inst().GetMainFrame())->OnChangeColourMap(wxCommandEvent());
	}

	Layout();
}

void VisualTree::CollapseNodes(float support)
{
	//m_tree = m_originalTree->Clone();
	m_tree->CollapseNodes(support);

	Layout();
}

void VisualTree::RestoreTree() 
{ 
	m_tree = m_originalTree->Clone(); 

	if(m_metadataInfo)
	{
		m_metadataInfo->SetMetadata(m_tree);	
		((PygmyFrame*)App::Inst().GetMainFrame())->OnChangeColourMap(wxCommandEvent());
	}

	Layout(); 
}

bool VisualTree::MouseLeftDown(const utils::Point& mousePt)
{
	// unselect previously selected node
	if(m_activeNode.node != NULL)
		m_activeNode.node->SetSelected(false);		

	// check if user has clicked on a node
	bool bSelected = false;
	foreach(VisualNode& visNode, m_visibleNodes)
	{
		visNode.visualMarker.SetVisibility(true);
		if(visNode.visualMarker.MouseLeftDown(mousePt))
		{
			bSelected = true;
			visNode.node->SetSelected(true);
			m_activeNode = visNode;

			break;
		}
	}

	return bSelected;
}

void VisualTree::Reroot()
{
	m_tree->Reroot(m_activeNode.node);

	// There is a bit of a complication here. If the root of a tree is changed,
	// some bootstrap values may be lost (i.e., because the split induced by the
	// previous root no longer exists). If the original rooting of the tree is 
	// later restored this data will be missing. As such, we explicitly restore
	// bootstrap values from the original tree here.
	std::vector< NodePhylo* > rootChildren = m_tree->GetRootNode()->GetChildren();
	foreach(NodePhylo* node, rootChildren)
	{
		std::vector< NodePhylo* > children = node->GetChildren();

		std::vector< NodePhylo* > originalNodes = m_originalTree->GetRootNode()->GetChildren();
		foreach(NodePhylo* originalNode, originalNodes)
		{
			std::vector< NodePhylo* > originalChildren = originalNode->GetChildren();

			bool bIdentical = true;
			foreach(NodePhylo* child, children)
			{
				bool bMatch = false;
				foreach(NodePhylo* originalChild, originalChildren)
				{
					if(child->GetId() == originalChild->GetId())
					{
						bMatch = true;
						break;
					}
				}

				if(!bMatch)
				{
					bIdentical = false;
					break;
				}
			}

			if(bIdentical)
			{
				node->SetBootstrapToParent(originalNode->GetBootstrapToParent());
				break;
			}
		}
	}

	Layout();
}

uint VisualTree::Parsimony()
{
	State::Inst().SetInternalNodeField(_T("Parsimony Data"));

	if(!m_parsimonyCalculator)
		m_parsimonyCalculator.reset(new utils::ParsimonyCalculator());

	std::wstring field = State::Inst().GetMetadataField();
	return m_parsimonyCalculator->Calculate(m_tree, field, m_metadataInfo->GetInfo(field).values);
}

utils::Tree<NodePhylo>::Ptr VisualTree::GetSelectedSubtree()
{
	// Clone tree as this subtree may be destroyed at any time
	utils::Tree<NodePhylo>::Ptr subtree = m_tree->Clone();

	// Find selected node in newly cloned tree
	NodePhylo* activeNode;
	std::vector<NodePhylo*> nodes = subtree->GetNodes();
	foreach(NodePhylo* node, nodes)
	{
		if(node->GetId() == m_activeNode.node->GetId())
		{
			activeNode = node;
			break;
		}
	}

	// create selected subtree
	subtree->SetRootNode(activeNode);
	activeNode->SetDistanceToParent(Node::NO_DISTANCE);
	activeNode->SetParent(NULL);

	return subtree;
}