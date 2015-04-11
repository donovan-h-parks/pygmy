//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/ViewportMouseEvents.hpp"

#include "../core/VisualObject.hpp"

using namespace pygmy;

ViewportMouseEvents& ViewportMouseEvents::Inst()
{
	static ViewportMouseEvents inst;
	return inst;
}

void ViewportMouseEvents::SetSelectedObject(VisualObjectPtr object) 
{ 
	// unselect current view
	if(m_selectedObject)
		m_selectedObject->SetSelected(false);

	// set new selected view
	m_selectedObject = object; 
	if(m_selectedObject)
		m_selectedObject->SetSelected(true);
}