//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VISUAL_COLOUR_MAP_
#define _VISUAL_COLOUR_MAP_

#include "../core/Precompiled.hpp"

namespace pygmy
{

/**
 * @class VisualColourMap
 * @brief Handles rendering and interaction with a visual representation of a colour map.
 */
class VisualColourMap
{
public:
	/** Constructor. */
	VisualColourMap(): m_width(0), m_fontOffset(5) {}

	/** Destructor. */
	virtual ~VisualColourMap() {}

	/** 
	 * @breif Render colour map. 
	 * @param width Width of viewport.
	 * @param height Height of viewport.
	 */
	void Render(int width, int height);

	/** Set colour map to visualize. */
	void SetColourMap(utils::ColourMapPtr colourMap) { m_colourMap = colourMap; }

	/** 
	 * @brief Set metadata info. 
	 * @param metadataInfo Summary information about each metadata field.
	 */
	void SetMetadataInfo(MetadataInfoPtr metadataInfo) { m_metadataInfo = metadataInfo; }

	/** Get width of colour map visualization. */
	float GetWidth() { return m_width; }

private:
	/** 
	 * @breif Render a discrete (or categorical) colour map.
	 * @param colourMap Discrete colour map to render.
	 * @param width Width of viewport.
	 * @param height Height of viewport.
	 */
	void RenderDiscreteMap(utils::ColourMapDiscretePtr colourMap, int width, int height);

	/** 
	 * @breif Render a continuous colour map.
	 * @param colourMap Continuous colour map to render.
	 * @param width Width of viewport.
	 * @param height Height of viewport.
	 */
	void RenderContinuousMap(utils::ColourMapContinuousPtr colourMap, int width, int height);

	/** 
	 * @brief Render marks indicate location of unique values on colour map. 
	 * @param width Width of viewport.
	 * @param height Height of viewport.
	 */
	void RenderUniqueValueMarks(int width, int height);
	
protected:
	/** Colour map to create visualization of. */
	utils::ColourMapPtr m_colourMap;

	/** Width of visualization. */
	float m_width;

	/** Summary information about metadata. */
	MetadataInfoPtr m_metadataInfo;

	/** Current metadata field of interest. */
	std::wstring m_field;

	/** Offset from colour map bar to field value labels. */
	uint m_fontOffset;
};

}

#endif
