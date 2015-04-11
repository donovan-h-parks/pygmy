//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VIEWPORT_HPP_
#define _VIEWPORT_HPP_

#include "../core/Precompiled.hpp"

namespace glUtils
{

class ContextGL;

/**
 * @brief Virtual base class for an OpenGL canvas.
 */
class Viewport : public wxGLCanvas
{
public:
	/** Constructor. */
	Viewport(wxWindow *parent, const wxWindowID id = -1, 
												const wxPoint& pos = wxDefaultPosition,
												const wxSize& size = wxDefaultSize, 
												long style = wxFULL_REPAINT_ON_RESIZE, 
												const wxString& name = _T("Viewport"));												
				
	/** Destructor. */
	virtual ~Viewport();

	/** 
	 * @brief Render the OpenGL scene. 
	 */
	void Render();

	/** 
	 * @brief Reconstruct display lists. 
	 * @param bRender True if OpenGL scene should be rendered.
	 */
	virtual void Redraw(bool bRender) = 0;

	/** Generate event indicating the viewport needs to be rendered. */
	void RenderEvent(bool b = false) { Refresh(b); }

	/** Indicate that the viewport needs to be rendered immediately. */
	void RenderNow() { Refresh(false); Update(); }

	/** Get flag indicating if the viewport is disabled. */
	bool IsDisabled() { return m_bDisabled; }

	/** Set flag indicating if the viewport is disabled. */
	void SetDisabled(bool state) { m_bDisabled = state; }

	/** Get width of viewport. */
	int GetWidth() { return m_width; }

	/** Get height of viewport. */
	int GetHeight() { return m_height; }

	/**
	 * @brief Save current scene to an image file.
	 *
	 * @param filename File to save image to.
	 */
	void SaveImage(const std::wstring& filename);
	
protected:
	/** 
	 * @brief Render the OpenGL scene. Called by Render() and OnPaint() which 
	 *				set up the appropriate device context. 
	 */
	virtual void RenderScene() = 0;

	/** Setup OpenGL canvas */
	virtual void InitCanvas() = 0;

	/** Connect all events handled by the viewport. */
	virtual void ConnectEvents();

	/** Disconnect all events handled by the viewport. */
	virtual void DisconnectEvents();

	/** Handle the erase event for the viewport panel which is generated
			whenever a window's background needs to be repainted. */
	virtual void OnEraseBackground(wxEraseEvent &WXUNUSED(event));

	/** Handle the paint event which is sent when a window's contents 
	  	needs to be repainted. */
	virtual void OnPaint(wxPaintEvent& event);

	/**
	 * @brief Save current scene to raster image file.
	 *
	 * @param filename File to save image to.
	 * @param extension Extension of file used to determine the image type (bmp, png, ...).
	 */
	void SaveRasterImage(const std::wstring& filename, const std::wstring& extension);

protected:	
	/** Viewport width and height. */
	int m_width, m_height;

	/** Flag indicating if viewport is disabled. */
	bool m_bDisabled;

	/** OpenGL context for viewport. */
	wxGLContext* m_contextGL;
};

}

#endif

