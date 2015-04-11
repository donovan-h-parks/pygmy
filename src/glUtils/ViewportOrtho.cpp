//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../glUtils/ViewportOrtho.hpp"
#include "../glUtils/ErrorGL.hpp"

#include "../utils/Log.hpp"
#include "../utils/StringTools.hpp"

using namespace glUtils;
using namespace utils;
using std::wstring;

ViewportOrtho::ViewportOrtho(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    : Viewport(parent, id, pos, size, style, name),
				m_zoomMin(0.0f), m_zoomMax(0.0f),	m_zoom(1.0f), 
				m_translateMin(0.0f), m_translateMax(0.0f), m_translate(0.0f)
{
	ConnectEvents();

	InitCanvas();
}

ViewportOrtho::~ViewportOrtho()
{
	DisconnectEvents();
}

void ViewportOrtho::ConnectEvents()
{
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( ViewportOrtho::OnSize ) );

	// mouse events
	this->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( ViewportOrtho::OnEnterWindow ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( ViewportOrtho::OnMouseLeftDblClick ) );
	this->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( ViewportOrtho::OnMouseRightDblClick ) );
	this->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( ViewportOrtho::OnMouseWheel ) );
}

void ViewportOrtho::DisconnectEvents()
{
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( ViewportOrtho::OnSize ) );

	// mouse events
	this->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( ViewportOrtho::OnEnterWindow ) );
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( ViewportOrtho::OnMouse ) );
	this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( ViewportOrtho::OnMouseLeftDblClick ) );
	this->Disconnect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( ViewportOrtho::OnMouseRightDblClick ) );
	this->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( ViewportOrtho::OnMouseWheel ) );
}

void ViewportOrtho::InitCanvas()
{
	m_contextGL->SetCurrent(*this);
	glUtils::ErrorGL::Check();

	// set GL viewport 
	GetClientSize(&m_width, &m_height);
	if(m_width == 0) 
		m_width = 1;

	if(m_height == 0)
		m_height = 1;

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		// White Background

	// setup antialiasing and blending to optimize appearance
	glShadeModel(GL_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// setup how depth testing will be performed
  glDisable(GL_DEPTH_TEST);	// disable depth testing since we are using a single 2D plane 
	glDepthMask(GL_FALSE);		// disable depth mask to improve visual quality of lines

	// setup desired default point size and line width
	glPointSize(1.0);
	glLineWidth(1.0f);
	glEnable(GL_LINE_STIPPLE);

	// setup texture filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// adjust orthographic projection settings
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLint) m_width, 0, (GLint) m_height);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, (GLint) m_width, (GLint) m_height);
	glLoadIdentity();

	glUtils::ErrorGL::Check();
}

void ViewportOrtho::OnSize(wxSizeEvent& event)
{
	m_contextGL->SetCurrent(*this);
	glUtils::ErrorGL::Check();

	if(!m_bDisabled)
	{
		// this is also necessary to update the context on some platforms
		//wxGLCanvas::OnSize(event);

		// set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
		GetClientSize(&m_width, &m_height);
		if(m_width == 0) m_width = 1;
		if(m_height == 0) m_height = 1;

		// adjust orthographic projection settings
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, (GLint) m_width, 0, (GLint) m_height);
		glMatrixMode(GL_MODELVIEW);
		glViewport(0, 0, (GLint) m_width, (GLint) m_height);
		glLoadIdentity();

		// indicate that the viewport dimensions have changed
		AdjustViewport();
		ZoomExtents();
		TranslationExtents();

		// save dimensions
		m_lastWidth = m_width;
		m_lastHeight = m_height;

		// repaint viewport
		Refresh(false);
	}

	glUtils::ErrorGL::Check();
}

void ViewportOrtho::OnEnterWindow( wxMouseEvent& WXUNUSED(event) )
{
	SetFocus();
}

void ViewportOrtho::OnMouse(wxMouseEvent& event)
{
	static bool bDragging = false;
	
	SetFocus();

	// *** Check if the user is moving the mouse around (with no buttons pressed!) ***
	if(event.Moving())
	{

	}

	// *** Check if the user is clicking a mouse button or dragging the mouse ***
	if(event.LeftDown())
	{
		// a dragging operation is starting
		bDragging = true;

		Point mousePt = Point(event.GetPosition().x, event.GetPosition().y);
		LeftClick(mousePt);
		m_sigMouseLeftClick(event);
	}
	else if(event.RightDown())
	{
		// a dragging operation is starting
		bDragging = true;

		Point mousePt = Point(event.GetPosition().x, event.GetPosition().y);
		RightClick(mousePt);
		m_sigMouseRightClick(event);
	}
	else if(event.LeftUp() || event.RightUp())
	{
		// done dragging
		bDragging = false;
	}
	else if(event.Dragging() && bDragging)	// using event.Dragging() fails when the File->Open dialog is used???
  {
		// we are in the middle of a dragging operation
  	wxPoint mousePos = event.GetPosition();

    if (event.LeftIsDown())
  	{
			TranslateView(mousePos.x - m_lastMousePos.x, mousePos.y - m_lastMousePos.y);
  	}
		else if(event.RightIsDown())
		{
			ScaleView(m_lastMousePos.x - mousePos.x, m_lastMousePos.y - mousePos.y);
		}
  }

	m_lastMousePos = event.GetPosition();
}

void ViewportOrtho::OnMouseLeftDblClick(wxMouseEvent& event)
{

}

void ViewportOrtho::OnMouseRightDblClick(wxMouseEvent& event)
{

}

void ViewportOrtho::OnMouseWheel(wxMouseEvent& event)
{
	int dWheel = event.GetWheelRotation()/event.GetWheelDelta();

	TranslateViewWheel(dWheel);
}

void ViewportOrtho::SetTranslation(float translation)
{
	m_translate = translation;

	if(m_translate > m_translateMax)
		m_translate = m_translateMax;
	else if(m_translate < m_translateMin)
		m_translate = m_translateMin;

	TranslationChanged();
}

void ViewportOrtho::SetZoom(float zoom)
{
	m_zoom = zoom;

	if(m_zoom > m_zoomMax)
		m_zoom = m_zoomMax;
	else if(m_zoom < m_zoomMin)
		m_zoom = m_zoomMin;

	ZoomChanged();
}

