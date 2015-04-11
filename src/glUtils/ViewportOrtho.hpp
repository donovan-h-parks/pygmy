//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VIEWPORT_ORTHO_HPP_
#define _VIEWPORT_ORTHO_HPP_

#include "../core/Precompiled.hpp"

#include "../glUtils/Viewport.hpp"

#include "../utils/Point.hpp"

namespace glUtils
{

/**
 * @brief Base class for an orthographic OpenGL canvas.
 */
class ViewportOrtho : public Viewport
{
public:
	/** Function signature for mouse left click signal. */
	typedef boost::signal<void (wxMouseEvent& event)> SigMouseLeftClick;

	/** Function signature for mouse right click signal. */
	typedef boost::signal<void (wxMouseEvent& event)> SigMouseRightClick;

public:
	/** Constructor. */
	ViewportOrtho(wxWindow *parent, const wxWindowID id = -1, 
												const wxPoint& pos = wxDefaultPosition,
												const wxSize& size = wxDefaultSize, 
												long style = wxFULL_REPAINT_ON_RESIZE, 
												const wxString& name = _T("ViewportOrtho"));

	/** Destructor. */
	virtual ~ViewportOrtho();
	
	/**
	 * @brief Set a slot (callback) to be signalled when a mouse left click events occurs.
	 * @param slot Slot (function) to call.
	 */
	void SignalMouseLeftClick(const SigMouseLeftClick::slot_type& slot) { m_sigMouseLeftClick.connect(slot); }

	/**
	 * @brief Set a slot (callback) to be signalled when mouse right click event occurs.
	 * @param slot Slot (function) to call.
	 */
	void SignalMouseRightClick(const SigMouseRightClick::slot_type& slot) { m_sigMouseRightClick.connect(slot); }

	/** 
	 * @brief Get zoom. 
	 * @return Current zoom value.
	 */
	virtual float GetZoom() const { return m_zoom; };

	/** 
	 * @brief Change translation. 
	  * @return Current translation value.
	 */
	virtual float GetTranslation() const { return m_translate; };
    
protected:
	/** Setup OpenGL canvas */
	virtual void InitCanvas();

	/** 
	 * @brief Change zoom. 
	 * @param zoom New zoom.
	 */
	virtual void SetZoom(float zoom);

	/** 
	 * @brief Change translation. 
	 * @param translation New translation.
	 */
	virtual void SetTranslation(float translation);

	/** Set min/max values for zooming. */
	virtual void ZoomExtents() = 0;

	/** Set min/max values for translation. */
	virtual void TranslationExtents() = 0;

	/** Called whenever zoom level has changed. */
	virtual void ZoomChanged() = 0;

	/** Called whenever translation changes. */
	virtual void TranslationChanged() = 0;

	// ** Window size has changed, so adjust the viewport size. */
	virtual void AdjustViewport() = 0;

	// ** Translate viewport. */
	virtual void TranslateView(int dx, int dy) = 0;

	// ** Scale viewport. */
	virtual void ScaleView(int dx, int dy) = 0;

	// ** Set default zoom level. */
	virtual void SetDefaultZoom() = 0;

	// ** Translate viewport due to scroll wheel. */
	virtual void TranslateViewWheel(int dWheel) = 0;

	/** 
	 * @brief A left mouse button click has occured.
	 * @param mousePt Mouse position in window when button was clicked.
	 */
	virtual void LeftClick(const utils::Point& mousePt) {}

	/** 
	 * @brief A right mouse button click has occured.
	 * @param mousePt Mouse position in window when button was clicked.
	 */
	virtual void RightClick(const utils::Point& mousePt) {}

	/** Connect all events handled by the viewport. */
	virtual void ConnectEvents();

	/** Disconnect all events handled by the viewport. */
	virtual void DisconnectEvents();

	/** Handle the size event which is sent when a window is resized. */
	virtual void OnSize(wxSizeEvent& event);

	/** Handle the window enter event which is sent what the mouse first
			moves over a window. */
	virtual void OnEnterWindow( wxMouseEvent& WXUNUSED(event) );

	/** Handle mouse move and button down events (translation + zooming). */
	virtual void OnMouse(wxMouseEvent& event);

	/** Handle left click. */
	virtual void OnMouseLeftClick(wxMouseEvent& event) {}

	/** Handle left double click (default: translation). */
	virtual void OnMouseLeftDblClick(wxMouseEvent& event);

	/** Handle right double click. */
	virtual void OnMouseRightDblClick(wxMouseEvent& event);

	/** Handle mouse wheel events (default: translation). */
	virtual void OnMouseWheel(wxMouseEvent& event);

protected:
	/** Signal that a mouse left click event has occured. */
	SigMouseLeftClick m_sigMouseLeftClick;

	/** Signal that a mouse right click event has occured. */
	SigMouseRightClick m_sigMouseRightClick;

	/** Limit minimum zoom factor to a reasonable level. */
	float m_zoomMin;

	/** Limit maximum zoom factor to a reasonable level. */
	float m_zoomMax;

	/** Limit minimum translation to a reasonable level. */
	float m_translateMin;

	/** Limit maximum translation to a reasonable level. */
	float m_translateMax;

	/** Last position of mouse. */
	wxPoint m_lastMousePos;

	/** Previous dimensions of viewport. */
	int m_lastWidth, m_lastHeight;

private:
	/** Current zoom factor to apply to viewport. */
	float m_zoom;

		/** Current translation to apply to viewport. */
	float m_translate;
};

}

#endif

