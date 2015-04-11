//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VISUAL_MARKER_
#define _VISUAL_MARKER_

#include "../core/Precompiled.hpp"

#include "../core/VisualObject.hpp"

#include "../utils/Point.hpp"
#include "../utils/Colour.hpp"

namespace pygmy
{

/** A marker to be rendered. */
class VisualMarker : public VisualObject
{
public:
	/** Different shapes of visual markers. */
	enum MARKER_SHAPE { CIRCLE, SQUARE, TRIANGLE, STAR, PLUS_SIGN, HEXAGON, DIAMOND, INVERTED_TRIANGLE };

	/** Different selection styles for visual markers. */
	enum SELECTION_STYLE { OUTLINE, FILL, FILL_AND_EXPAND };

public:
	/** Constructor. */
	VisualMarker();

	/** Constructor. */
	VisualMarker(utils::Colour colour, float size, MARKER_SHAPE shape, SELECTION_STYLE style, const utils::Point& position);

	/** Destructor. */
	~VisualMarker() {}

	/** Render marker. */
	void Render();

	/** Get colour of marker. */
	const utils::Colour& GetColour() const { return m_colour; }

	/** Set colour of marker. */
	void SetColour(const utils::Colour& colour) { m_colour = colour; }

	/** Get size of marker. */
	const float GetSize() const { return m_size; }

	/** Set size of marker. */
	void SetSize(float size) { m_size = size; }

	/** Set position of marker. */
	void SetPosition(const utils::Point& pos) { m_position = pos; }

	/** Get position of marker. */
	const utils::Point& GetPosition() const { return m_position; }

	/** Set shape of marker. */
	void SetShape(MARKER_SHAPE shape) { m_shape = shape; }

	/** Get shape of marker. */
	MARKER_SHAPE GetShape() const { return m_shape; }

	/** Set selection style for marker. */
	void SetSelectionStyle(SELECTION_STYLE style) { m_selectionStyle = style; }

	/** Get selection style for marker. */
	SELECTION_STYLE GetSelectionStyle() const { return m_selectionStyle; }

	/** 
	 * @brief Process mouse left button down events. 
	 * @param mousePt Screen position of mouse.
	 * @return True if visual tree is processing the event, else false.
	 */
	bool MouseLeftDown(const utils::Point& mousePt);

protected:
	/** Render marker with the specified size and shape. */
	void RenderMarker(float size, MARKER_SHAPE shape);

private:
	/** Position of marker. */
	utils::Point m_position;

	/** Desired shape of marker. */
	MARKER_SHAPE m_shape;

	/** Colour of marker. */
	utils::Colour m_colour;

	/** Size of marker. */
	float m_size;

	/** Selection style of marker. Indicates how is should be rendered when selected. */
	SELECTION_STYLE m_selectionStyle;
};

}

#endif
