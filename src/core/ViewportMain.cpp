//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/ViewportMain.hpp"
#include "../core/ViewportOverview.hpp"
#include "../core/State.hpp"
#include "../core/App.hpp"
#include "../core/VisualColourMap.hpp"
#include "../core/VisualTree.hpp"
#include "../core/NodePhylo.hpp"
#include "../core/Filter.hpp"

#include "../glUtils/ErrorGL.hpp"
#include "../glUtils/Font.hpp"

#include "../utils/Log.hpp"
#include "../utils/StringTools.hpp"
#include "../utils/Tree.hpp"
#include "../utils/Colour.hpp"

using namespace pygmy;
using namespace glUtils;
using namespace utils;

//*** Class Member Functions ***

ViewportMain::ViewportMain(wxWindow *parent, const wxWindowID id, 
							const wxPoint& pos, const wxSize& size, long style,	const wxString& name):
							ViewportOrtho(parent, id, pos, size, style, name)
{

}

void ViewportMain::Redraw(bool bRender)
{
	m_contextGL->SetCurrent(*this);
	glUtils::ErrorGL::Check();

	// Redraw the overview tree so it reflects the changes made to the tree
	m_overview->Redraw(bRender);

	if(bRender)
		Refresh(false);

	glUtils::ErrorGL::Check();
}

void ViewportMain::RenderScene()
{
	m_contextGL->SetCurrent(*this);
	glUtils::ErrorGL::Check();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(m_visualColourMap)
		m_visualColourMap->Render(m_width, m_height);

	if(m_visualTree)
	{
		m_visualTree->Render(m_width, m_height, GetTranslation(), ViewportOrtho::GetZoom());

		if(m_overview)
		{
			// render the overview scene to reflect changes in the viewport
			m_overview->TranslationFraction(TranslationFraction());
			m_overview->ViewportHeightFraction(m_visualTree->GetViewportHeightFraction());
			m_overview->Render();
		}
	}

  SwapBuffers();

	glUtils::ErrorGL::Check();

}

void ViewportMain::TranslateView(int dx, int dy)
{
	// translate view
	SetTranslation(GetTranslation() + State::Inst().GetTranslationSensitivity()*dy);

	Refresh(false);
}

void ViewportMain::ScaleView(int dx, int dy)
{
	float zoomSensitivity = State::Inst().GetZoomSensitivity();
	SetZoom(ViewportOrtho::GetZoom() + zoomSensitivity*(dy)*ViewportOrtho::GetZoom());

	Refresh(false);
}

void ViewportMain::SetZoom(float zoom)
{
	float previousZoom = ViewportOrtho::GetZoom();
	float previousTranslation = GetTranslation();

	// bounds check and update any quantities dependent on the zoom
	ViewportOrtho::SetZoom(zoom);

	// modify translation so the middle line does not move during zooming
	SetTranslation(previousTranslation + (previousTranslation+m_height*0.5)*(ViewportOrtho::GetZoom()-previousZoom)/previousZoom);

	Refresh(false);
}

void ViewportMain::SetDefaultZoom()
{
	// reset zooming factor to default value
	float targetZoom;
	if((m_height-2*State::Inst().GetBorderSize().y) > m_visualTree->GetTreeHeight())
		targetZoom = (m_height-2*State::Inst().GetBorderSize().y)/m_visualTree->GetTreeHeight();
	else
		targetZoom = m_zoomMin*State::Inst().GetZoomDefault();

	ViewportOrtho::SetZoom(targetZoom);
}

void ViewportMain::TranslateViewWheel(int dWheel)
{
	SetTranslation(GetTranslation() + State::Inst().GetScrollSensitivity()*dWheel);

	Refresh(false);
}

void ViewportMain::ModifiedFont() 
{ 
	if(!m_visualTree)
		return;

	m_visualTree->LabelBoundingBoxes(); 
	AdjustViewport(); 
	ZoomExtents();
}

void ViewportMain::ZoomExtents()
{
	if(m_visualTree)
	{
		// calculate extents of zoom
		m_zoomMin = 1.0f; 
		m_zoomMax = m_zoomMin*State::Inst().GetZoomMax();
		if(m_zoomMax < (m_height-2*State::Inst().GetBorderSize().y)/m_visualTree->GetTreeHeight())
		{
			// make sure the maximum zoom is large enough to allow
			// small graphs to fill the entire viewport
			m_zoomMax = (m_height-2*State::Inst().GetBorderSize().y)/m_visualTree->GetTreeHeight();
		}

		// make sure zoom factor is within allowable range
		ViewportOrtho::SetZoom(ViewportOrtho::GetZoom());

		Refresh(false);
	}
}

void ViewportMain::TranslationExtents()
{
	if(!m_visualTree)
		return;

	// calculate extents of translation
	m_translateMin = 0;	// negative translations are not allowed

	m_translateMax = m_visualTree->GetTreeHeight()*ViewportOrtho::GetZoom() + 2*State::Inst().GetBorderSize().y - m_height;
	if(m_translateMax < 0)
		m_translateMax = 0;

	// make sure translation factor is within allowable range
	SetTranslation(GetTranslation());

	Refresh(false);
}

void ViewportMain::AdjustViewport()
{
	if(!m_visualTree)
		return;

	// adjust translation so mid-line of the viewport is unchanged
	SetTranslation(GetTranslation() + 0.5f*(m_lastHeight-m_height));

	Refresh(false);
}

void ViewportMain::ZoomChanged()
{
	if(!m_visualTree)
		return;

	m_visualTree->CalculateTreeDimensions(m_width, m_height, ViewportOrtho::GetZoom());
	TranslationExtents();
}

void ViewportMain::CenterNode(uint id)
{
	// find node with specified id
	std::vector< NodePhylo* > leaves = m_visualTree->GetTree()->GetLeaves();
	NodePhylo* node = NULL;
	foreach(NodePhylo* leaf, leaves)
	{
		if(leaf->GetId() == id)
		{
			node = leaf;
			break;
		}
	}

	float posY = node->GetPosition().y * m_visualTree->GetTreeHeight() * ViewportOrtho::GetZoom() + State::Inst().GetBorderSize().y;
	float translatedY = posY-GetTranslation();

	if(translatedY < 0 || translatedY > GetSize().y)
	{
		// Node is currently outside the viewport.
		SetTranslation(posY-0.5*m_height);
	}

	Refresh(false);
}

void ViewportMain::TranslationFraction(float frac)
{
	SetTranslation(frac*(m_visualTree->GetTreeHeight()*ViewportOrtho::GetZoom()
										+ 2*State::Inst().GetBorderSize().y) + State::Inst().GetBorderSize().y);

	Refresh(false);
}

float ViewportMain::TranslationFraction()
{
	if(!m_visualTree)
		return 0.0f;

	float frac = (GetTranslation() - State::Inst().GetBorderSize().y) 
									/ (m_visualTree->GetTreeHeight()*ViewportOrtho::GetZoom() + State::Inst().GetBorderSize().y);
	if(frac < 0.0f)
		frac = 0.0f;

	return frac;
}

void ViewportMain::SetBranchStyle(VisualTree::BRANCH_STYLE branchStyle) 
{ 
	if(!m_visualTree)
		return;

	if(m_visualTree->GetBranchStyle() != branchStyle)
	{
		m_visualTree->SetBranchStyle(branchStyle);
		Redraw(true);
	}
}

void ViewportMain::SetTree(VisualTreePtr visualTree)
{
	m_visualTree = visualTree;

	// calculate bounding boxes for all leaf node labels
	m_visualTree->LabelBoundingBoxes();
	m_visualTree->CalculateTreeDimensions(m_width, m_height, ViewportOrtho::GetZoom());

	// set min/max values for zoom
	ZoomExtents();

	// set initial zoom:
	Point border = State::Inst().GetBorderSize();
	if(m_height-2*border.y > m_visualTree->GetTreeHeight())
	{
		// The entire tree can fit within the viewport, so we set the zoom
		// so it fills the entire viewport.
		SetZoom((m_height-2*border.y) / m_visualTree->GetTreeHeight());
		SetTranslation(0);
	}
	else
	{
		// Since the entire tree can't be displayed in the viewport, set the
		// zoom factor to the default value and place the node of the graph
		// at the center of the viewport.
		SetZoom(m_zoomMin*State::Inst().GetZoomDefault());
		SetTranslation((m_visualTree->GetTreeHeight() + border.x) * ViewportOrtho::GetZoom()/2 - m_height/2);
	}
	
	// Rebuild any display lists and render the scene
	Redraw(false);
}

void ViewportMain::SetColourMap(VisualColourMapPtr visualColourMap)
{
	m_visualColourMap = visualColourMap;

	// Rebuild any display lists and render the scene
	Redraw(true);
}

