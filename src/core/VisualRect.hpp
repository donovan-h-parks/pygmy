//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VISUAL_RECT_
#define _VISUAL_RECT_

#include "../core/Precompiled.hpp"

#include "../core/VisualObject.hpp"

#include "../utils/Common.hpp"
#include "../utils/Colour.hpp"

namespace pygmy
{

/** A rectangle to be rendered. */
class VisualRect : public VisualObject
{
public:
	/** Rect type. Used to optimize rendering. */
	enum RECT_TYPE { HORIZONTAL, VERTICAL, SLANTED };

public:
	/** Constructor. */
	VisualRect(const utils::Colour& startColour = utils::Colour(1.0f, 1.0f, 1.0f), 
							const utils::Colour& endColour = utils::Colour(1.0f, 1.0f, 1.0f),
							const utils::Rect& rect = utils::Rect(), RECT_TYPE type = SLANTED)
							: m_startColour(startColour), m_endColour(endColour), m_rect(rect), m_type(type)  
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

	/** Get lower, left point of rect. */
	const utils::Point& GetLowerLeftPt() const { return m_rect.ll; }

	/** Set lower, left point of rect. */
	void SetLowerLeftPt(const utils::Point& pt) { m_rect.ll = pt; }

	/** Get upper, left point of rect. */
	const utils::Point& GetUpperLeftPt() const { return m_rect.ul; }

	/** Set upper, left point of rect. */
	void SetUpperLeftPt(const utils::Point& pt) { m_rect.ul = pt; }

	/** Get upper, right point of rect. */
	const utils::Point& GetUpperRightPt() const { return m_rect.ur; }

	/** Set upper, right point of rect. */
	void SetUpperRightPt(const utils::Point& pt) { m_rect.ur = pt; }

	/** Get lower, right point of rect. */
	const utils::Point& GetLowerRightPt() const { return m_rect.lr; }

	/** Set lower, right point of rect. */
	void SetLowerRightPt(const utils::Point& pt) { m_rect.lr = pt; }

	/** Get type of rectangle. */
	RECT_TYPE GetType() { return m_type; }

	/** Set type of rectangle. */
	void SetType(RECT_TYPE type) { m_type = type; }

	/** Get copy of the rectangle. */
	const utils::Rect& Rect() const { return m_rect; }

protected:
	/** Render rectangle. */
	void RenderRect(const utils::Colour& startColour, const utils::Colour& endColour, const utils::Rect& rect);

protected:
	/** Rectangle to be rendered with above visual properties. */
	utils::Rect m_rect;

	/** Initial colour of rectangle. */
	utils::Colour m_startColour;

	/** End colour of rectangle. */
	utils::Colour m_endColour;

	/** Specifies type of rectangle. Used to optimize rendering. */
	RECT_TYPE m_type;
};

}

#endif
