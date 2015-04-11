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
#include "../core/ViewportOverview.hpp"
#include "../core/ViewportMain.hpp"
#include "../core/State.hpp"
#include "../core/Filter.hpp"

#include "../glUtils/ErrorGL.hpp"

#include "../utils/StringTools.hpp"

using namespace pygmy;
using namespace utils;

//*** Member Functions***

ViewportOverview::ViewportOverview(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    : ViewportOrtho(parent, id, pos, size, style, name), m_borderX(5), m_borderY(5)
{
	m_treeList = glGenLists(1);
	m_textSearchList = glGenLists(1);
}

ViewportOverview::~ViewportOverview()
{

}

void ViewportOverview::SetTree(VisualTreePtr visualTree)
{
	m_visualTree = visualTree;
	
	// draw the new graph
	Redraw(true);
}

void ViewportOverview::TranslateView(int dx, int dy)
{
	// move viewport window in accordance with the amount of mouse movement
	float curTransFrac = m_viewport->TranslationFraction();
	float transFrac = float(dy)/(m_height - 2*m_borderY);

	float newFrac = curTransFrac - transFrac;
	if(newFrac < 0.0) newFrac = 0.0;
	if(newFrac > 1.0f) newFrac = 1.0f;

	m_viewport->TranslationFraction(newFrac);
}

void ViewportOverview::TranslateViewWheel(int dWheel)
{
	const float OVERVIEW_WHEEL_SENSITIVITY = 0.25;

	// move viewport window a set fraction of its height
	float curTransFrac = m_viewport->TranslationFraction();
	float transFrac = curTransFrac + OVERVIEW_WHEEL_SENSITIVITY*m_viewportHeightFrac*dWheel;

	m_viewport->TranslationFraction(transFrac);
}

void ViewportOverview::LeftClick(const utils::Point& mousePt)
{
	// Note: Mouse (window) have 0,0 at the top, left
	// whereas the viewport has 0,0 at the bottom, left
	float y = m_height - mousePt.y;

	// determine where mouse is on tree
	float frac = (y- m_borderY) / (m_height - 2*m_borderY);

	// center the viewport at this point
	frac -= 0.5*m_viewportHeightFrac;
	
	// bound position
	if(frac < 0.0f) frac = 0.0f;
	if(frac > 1.0f) frac = 1.0f;

	m_viewport->TranslationFraction(frac);
}

void ViewportOverview::Redraw(bool bRender)
{
	if(!m_visualTree || m_bDisabled)
		return;

	RedrawTree(false);
	RedrawTextSearch(false);

	if(bRender)
		Refresh(false);
}

void ViewportOverview::RedrawTree(bool bRender)
{
	m_contextGL->SetCurrent(*this);
	glUtils::ErrorGL::Check();

	if(!m_visualTree)
		return;

	// *** Draw the tree. ***
	glNewList(m_treeList, GL_COMPILE);
	{
		glDisable(GL_LINE_SMOOTH);

		glLineWidth(State::Inst().GetOverviewLineWidth());
		int thicknessMajor = int(1 + State::Inst().GetOverviewLineWidth()*0.5);
		int thicknessMinor = int((State::Inst().GetOverviewLineWidth()-0.5)*0.5);

		// scale factor for tree (Note: glScalef() is not used as we want lines to be pixel aligned)
		float sx = m_width - 2*m_borderX;
		float sy = m_height - 2*m_borderY;

		// translation factor for tree (Note: glTranslatef() is not used as we want lines to be pixel aligned)
		float dx = m_borderX + 0.5;
		float dy = m_borderY + 0.5;
		
		// *** Draw overview tree
		std::vector<NodePhylo*> nodes = m_visualTree->GetTree()->GetNodes();
		foreach(NodePhylo* node, nodes)
		{			
			// adjust position of nodes based on desired orientation
			Point parentPos = node->GetPosition();
			
			// Draw branches
			float yMin = 1000.0f, yMax = 0.0f;
			std::vector<NodePhylo*> children = node->GetChildren();
			foreach(NodePhylo* child, children)
			{				
				Point childPos = child->GetPosition();
				
				// draw horizontal line
				glBegin(GL_QUADS);
					if(State::Inst().GetColourOverviewTree())
						node->GetColour().SetColourOpenGL();
					else
						glColor3f(0.5f, 0.5f, 0.5f);
					glVertex2i(int(parentPos.x*sx + dx), int(childPos.y*sy + dy + thicknessMajor));
					glVertex2i(int(parentPos.x*sx + dx), int(childPos.y*sy + dy - thicknessMinor));

					if(State::Inst().GetColourOverviewTree())
							child->GetColour().SetColourOpenGL();
						else
							glColor3f(0.5f, 0.5f, 0.5f);
					glVertex2i(int(childPos.x*sx + dx), int(childPos.y*sy + dy - thicknessMinor));
					glVertex2i(int(childPos.x*sx + dx), int(childPos.y*sy + dy + thicknessMajor));						
				glEnd();

				if(yMin > childPos.y) 
					yMin = childPos.y;

				if(yMax < childPos.y) 
					yMax = childPos.y;
			}

			// It is better to draw a single vertical line as this reduces the number of line segments
			// that must be rendered and ensures that only a single crisp line is drawn (as opposed to multiple
			// overlapping lines which can cause strange visual artifacts).
			if(!node->IsLeaf())
			{
				if(State::Inst().GetColourOverviewTree())
					node->GetColour().SetColourOpenGL();
				else
					glColor3f(0.5f, 0.5f, 0.5f);

				// Draw vertical line adjusting for the width of the line being drawn. For some reason, the offset
				// needed to account for the line width is different for the start and end of the line (???).
				glBegin(GL_QUADS); 
					glVertex2i(int(parentPos.x*sx + dx + thicknessMajor), int(parentPos.y*sy + dy - thicknessMinor));
					glVertex2i(int(parentPos.x*sx + dx - thicknessMinor), int(parentPos.y*sy + dy - thicknessMinor));
					glVertex2i(int(parentPos.x*sx + dx - thicknessMinor), int(yMax*sy + dy + thicknessMajor));
					glVertex2i(int(parentPos.x*sx + dx + thicknessMajor), int(yMax*sy + dy + thicknessMajor));
				glEnd();

				glBegin(GL_QUADS); 
					glVertex2i(int(parentPos.x*sx + dx + thicknessMajor), int(yMin*sy + dy - thicknessMinor));
					glVertex2i(int(parentPos.x*sx + dx - thicknessMinor), int(yMin*sy + dy - thicknessMinor));
					glVertex2i(int(parentPos.x*sx + dx - thicknessMinor), int(parentPos.y*sy + dy + thicknessMajor));
					glVertex2i(int(parentPos.x*sx + dx + thicknessMajor), int(parentPos.y*sy + dy + thicknessMajor));
				glEnd();
			}
		}		

		glEnable(GL_LINE_SMOOTH);
	}
  glEndList();

	glUtils::ErrorGL::Check();
}

void ViewportOverview::RedrawTextSearch(bool bRender)
{
	m_contextGL->SetCurrent(*this);
	glUtils::ErrorGL::Check();

	if(!m_visualTree)
		return;

	glNewList(m_textSearchList, GL_COMPILE);
	{
		float adjHeight = m_height-2*m_borderY;
		
		std::vector<NodePhylo*> nodes = m_visualTree->GetTree()->GetNodes();
		foreach(NodePhylo* node, nodes)
		{
			if(m_searchFilter->Filtered(node->GetId()))
			{
				Point parentPos = node->GetPosition();

				glColor3f(0.9f, 0.1f, 0.14f);

				float yPos = parentPos.y*adjHeight + m_borderY;					
				glBegin(GL_QUADS);
					glVertex2f(m_width-m_borderX, yPos - 2);
					glVertex2f(m_width, yPos - 2);
					glVertex2f(m_width, yPos + 2);
					glVertex2f(m_width-m_borderX, yPos + 2);
				glEnd();		
			
			}
		}
	}
  glEndList();

	if(bRender)
		Refresh(false);

	glUtils::ErrorGL::Check();
}

void ViewportOverview::RenderScene()
{
	const float MIN_POS_INDICATOR_HEIGHT = 5.0f;
	m_contextGL->SetCurrent(*this);

	glUtils::ErrorGL::Check();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ------------------ render the tree ---------------
	if(m_visualTree)
	{		
		// *** Render overview tree. ***
		glPushMatrix();	
		{			
			glCallList(m_treeList);
		}
		glPopMatrix();

		// *** Highlight text search results
		glPushMatrix();		
		{		
			glCallList(m_textSearchList);			
		}
		glPopMatrix();

		// *** Render position indicator. ***
		if(State::Inst().GetOverviewPositionOverlay())
		{
			glPushMatrix();	
			{
				glTranslatef(0.0f, m_borderY, 0.0f);
				glScalef(m_width-m_borderX, m_height - 2*m_borderY, 1.0f);

				glColor4f(0.6f, 0.8f, 0.8f, 0.5f);

				// ensure position indicator is always visible
				if(m_viewportHeightFrac*(m_height - 2*m_borderY) >= MIN_POS_INDICATOR_HEIGHT)
				{
					glBegin(GL_QUADS);
						glVertex2f(0.0f, m_translationFrac);
						glVertex2f(1.0f, m_translationFrac);
						glVertex2f(1.0f, m_translationFrac + m_viewportHeightFrac);
						glVertex2f(0.0f, m_translationFrac + m_viewportHeightFrac);
					glEnd();
				}
				else
				{
					// determine height that is equivalent to the desired minimum height
					float height = MIN_POS_INDICATOR_HEIGHT / (m_height - 2*m_borderY);
					float midPoint = m_translationFrac + 0.5*m_viewportHeightFrac;
					glBegin(GL_QUADS);
						glVertex2f(0.0f, midPoint - 0.5*height);
						glVertex2f(1.0f, midPoint - 0.5*height);
						glVertex2f(1.0f, midPoint + 0.5*height);
						glVertex2f(0.0f, midPoint + 0.5*height);
					glEnd();
				}
			}
			glPopMatrix();
		}
	}

  SwapBuffers();

	glUtils::ErrorGL::Check();
}