//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/VisualLine.hpp"
#include "../core/App.hpp"

#include "../glUtils/ErrorGL.hpp"

using namespace pygmy;
using namespace utils;

void VisualLine::RenderLine(const Colour& startColour, const Colour& endColour, VisualLine::LINE_STYLE lineStyle, 
														float size, const utils::Line& line)
{
	const int REPEAT_FACTOR = 5;

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(REPEAT_FACTOR, lineStyle);

	glLineWidth(size);	

	glBegin(GL_LINES);
		glColor4f(startColour.GetRed(), startColour.GetGreen(), startColour.GetBlue(), startColour.GetAlpha());
		glVertex2f(line.start.x, line.start.y);

		glColor4f(endColour.GetRed(), endColour.GetGreen(), endColour.GetBlue(), endColour.GetAlpha());
		glVertex2f(line.end.x, line.end.y);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

void VisualLine::Render()
{
	if(!m_bVisible)
		return;

	glUtils::ErrorGL::Check();

	if(m_bSelected)
	{
		RenderLine(Colour(1.0f, 0.0f, 0.0f), Colour(1.0f, 0.0f, 0.0f), m_lineStyle,	m_width + 2, m_line);
	}

	RenderLine(m_startColour, m_endColour, m_lineStyle, m_width, m_line);

	glUtils::ErrorGL::Check();
}
