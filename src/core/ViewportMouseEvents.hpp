//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VIEWPORT_MOUSE_EVENTS_HPP_
#define _VIEWPORT_MOUSE_EVENTS_HPP_

#include "../core/DataTypes.hpp"

namespace pygmy
{

/**
 * @class ViewportMouseEvents
 * @brief Singleton class for handling mouse events within the main viewport.
 */
class ViewportMouseEvents
{
public:
	/** Destructor */
	~ViewportMouseEvents() { }

	/** Get the one and only instance of the settings class. */
	static ViewportMouseEvents& Inst();

	/** 
	 * @brief Set currently selected visual object.
	 * @param view Smart pointer to currently selected view.
	 */
	void SetSelectedObject(VisualObjectPtr object);

	/** Get currently selected object. */
	VisualObjectPtr GetSelectedObject() { return m_selectedObject; }

	/** 
	 * @brief Set currently active right-click object.
	 * @param view Smart pointer to currently active right-click view.
	 */
	void SetRightClickObject(VisualObjectPtr view) { m_rightClickObject = view; }

	/** Get currently active right-click object. */
	VisualObjectPtr GetRightClickObject() { return m_rightClickObject; }

protected:
	/** Private singleton constructor (must instantiate this class through Inst()). */
	ViewportMouseEvents() {}

	/** Private copy constructor (must instantiate this class through Inst()). */
  ViewportMouseEvents(const ViewportMouseEvents&);

	/** Private assignment constructor (must instantiate this class through Inst()). */
  ViewportMouseEvents& operator= (const ViewportMouseEvents&);

private:
	/** Currently selected visual object. */
	VisualObjectPtr m_selectedObject;

	/** Currently selected right-click object. */
	VisualObjectPtr m_rightClickObject;
};

}

#endif