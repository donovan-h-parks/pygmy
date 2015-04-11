//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VISUAL_LINE_
#define _VISUAL_LINE_

#include "../core/Precompiled.hpp"

#include "../core/VisualObject.hpp"

#include "../utils/Line.hpp"
#include "../utils/Point.hpp"
#include "../utils/Colour.hpp"

namespace pygmy
{

/** A line to be rendered. */
class VisualLine : public VisualObject
{
public:
	/** Line styles. */
	enum LINE_STYLE { SOLID = 0xFFFF, SHORT_DASH = 0xAAAA, LONG_DASH = 0xEEEE };

public:
	/** Constructor. */
	VisualLine(const utils::Colour& startColour = utils::Colour(1.0f, 1.0f, 1.0f), 
							const utils::Colour& endColour = utils::Colour(1.0f, 1.0f, 1.0f),
							float width = 1.0, LINE_STYLE lineStyle = SOLID, const utils::Line& line = utils::Line())
							: m_startColour(startColour), m_endColour(endColour), m_width(width), m_lineStyle(lineStyle), m_line(line)  
	{
	
	}

	/** Render line. */
	void Render();

	/** Get colour of start point. */
	const utils::Colour& GetStartColour() const { return m_startColour; }

	/** Set colour of start point. */
	void SetStartColour(const utils::Colour& colour) { m_startColour = colour; }

	/** Get colour of end point. */
	const utils::Colour& GetEndColour() const { return m_endColour; }

	/** Set colour of end point. */
	void SetEndColour(const utils::Colour& colour) { m_endColour = colour; }

	/** Get width of line. */
	const float GetWidth() const { return m_width; }

	/** Set width of line. */
	void SetWidth(float size) { m_width = size; }

	/** Get line style. */
	const LINE_STYLE GetLineStyle() const { return m_lineStyle; }

	/** Set line style. */
	void SetLineStyle(LINE_STYLE lineStyle) { m_lineStyle = lineStyle; }

	/** Get start point of line. */
	const utils::Point& GetStartPt() const { return m_line.start; }

	/** Set start point of line. */
	void SetStartPt(const utils::Point& pt) { m_line.start = pt; }

	/** Get end point of line. */
	const utils::Point& GetEndPt() const { return m_line.end; }

	/** Set end point of line. */
	void SetEndPt(const utils::Point& pt) { m_line.end = pt; }

	/** Get copy of line. */
	const utils::Line& Line() const { return m_line; }

protected:
	/** Render line. */
	void RenderLine(const utils::Colour& startColour, const utils::Colour& endColour, 
										VisualLine::LINE_STYLE lineStyle, float size, const utils::Line& line);

protected:
	/** Line style for line. */
	LINE_STYLE m_lineStyle;

	/** Lines to be rendered with above visual properties. */
	utils::Line m_line;

	/** Colour of start point. */
	utils::Colour m_startColour;

	/** Colour of end point. */
	utils::Colour m_endColour;

	/** Width of line. */
	float m_width;
};

}

#endif
