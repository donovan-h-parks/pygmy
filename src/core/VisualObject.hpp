//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VISUAL_OBJECT_
#define _VISUAL_OBJECT_

#include "../core/Precompiled.hpp"

#include "../utils/Colour.hpp"

#include "../utils/Point.hpp"

namespace pygmy
{

/** Virtual base class for graphical elements. */
class VisualObject
{
public:
	/** Constructor. */
	VisualObject(): m_bVisible(true), m_bSelected(false) {}

	/** Render view. */
	virtual void Render() {}

	/** Set the visibility of view. */
	virtual void SetVisibility( bool visible ) {	m_bVisible = visible;	}

	/** Set the visibility of view. */
	virtual bool IsVisible() { return m_bVisible;	}

	/** Set flag indicating if view is selected or not. */
	virtual void SetSelected(bool state) { m_bSelected = state; }

	/** Determine if view is currently selected. */
	virtual bool IsSelected() { return m_bSelected; }

	/** Show properties dialog for this view. */
	virtual void ShowPropertiesDlg() {}

	/** 
	 * @brief Process mouse left button down events. 
	 * @param mousePt Screen position of mouse.
	 * @return True if view is processing the event, else false.
	 */
	virtual bool MouseLeftDown(const utils::Point& mousePt) { return false; }

	/** 
	 * @brief Process mouse left button up events. 
	 * @param mousePt Screen position of mouse.
	 */
	virtual void MouseLeftUp(const utils::Point& mousePt) { return; }

	/** 
	 * @brief Process mouse left button float click events. 
	 * @param mousePt Screen position of mouse.
	 */
	virtual void MouseLeftDblClick(const utils::Point& mousePt) { return; }

	/** 
	 * @brief Process mouse right button down events. 
	 * @param mousePt Screen position of mouse.
	 * @param popupMenu Popup menu to populate.
	 * @return True if view is processing the event, else false.
	 */
	bool MouseRightDown(const utils::Point& mousePt, wxMenu& popupMenu);

	/** 
	 * @brief Process mouse dragging events. 
	 * @param mousePt Screen position of mouse.
	 */
	virtual void MouseDragging(const utils::Point& mousePt) { return; }

	/** 
	 * @brief Process mouse moving events. 
	 * @param mousePt Screen position of mouse.
	 * @return True if the OpenGL viewport should be refreshed.
	 */
	virtual bool MouseMove(const utils::Point& mousePt) { return false; }

	/** 
	 * @brief Process keyboard events. 
	 * @param mousePt Screen position of mouse.
	 */
	virtual void KeyboardEvent(wxKeyEvent& event) { return; }

protected:
	/** Flag indicating if object should be visible or not. */
	bool m_bVisible;

	/** Flag indicating if object is currently selected. */
	bool m_bSelected;

};

}

#endif
