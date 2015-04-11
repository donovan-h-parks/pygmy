//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/VisualRect.hpp"
#include "../core/App.hpp"

#include "../glUtils/ErrorGL.hpp"

using namespace pygmy;
using namespace utils;

void VisualRect::RenderRect(const Colour& startColour, const Colour& endColour, const utils::Rect& rect)
{
	if(m_type == SLANTED)
	{
		uint dx = uint(fabs(rect.ll.x - rect.ul.x));
		uint dy = uint(fabs(rect.ll.y - rect.ul.y));

		uint width = dx;
		if(width < dy)
			width = dy;

		glLineWidth(width);

		glBegin(GL_LINES); 		
			startColour.SetColourOpenGL();
			glVertex2i(rect.ll.x, rect.ll.y);

			endColour.SetColourOpenGL();
			glVertex2i(rect.lr.x, rect.lr.y);
		glEnd();	
	}
	else
	{
		glBegin(GL_QUADS);
			startColour.SetColourOpenGL();
			glVertex2i(rect.ll.x, rect.ll.y);
			glVertex2i(rect.ul.x, rect.ul.y);

			endColour.SetColourOpenGL();
			glVertex2i(rect.ur.x, rect.ur.y);
			glVertex2i(rect.lr.x, rect.lr.y);						
		glEnd();
	}
}

void VisualRect::Render()
{
	if(!m_bVisible)
		return;

	glUtils::ErrorGL::Check();

	RenderRect(m_startColour, m_endColour, m_rect);

	if(m_bSelected)
	{
		RenderRect(Colour(1.0f, 0.0f, 0.0f), Colour(1.0f, 0.0f, 0.0f), m_rect);
	}

	glUtils::ErrorGL::Check();
}
