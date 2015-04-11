//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _COLOUR_MAP_CONTINUOUS_
#define _COLOUR_MAP_CONTINUOUS_

#include "../utils/ColourMap.hpp"

#include "../utils/Colour.hpp"

namespace utils
{

/**
 * @class ColourMapContinuous
 * @brief Allow colours to be obtained from a continuous spectrum.
 */
class ColourMapContinuous: public ColourMap
{
public:
	/** Constructor. */
	ColourMapContinuous(const std::wstring& name = _T("<no name>"), TYPE type = CONTINUOUS): ColourMap(name, type) {}

	/** Destructor. */
	virtual ~ColourMapContinuous() {}
	
	/** Interpolate colour from colour map. */
	virtual Colour GetColour(float value, float minValue, float maxValue) const;

	/** Get colour from underlying colour map. */
	Colour GetColour(uint index) const { return ColourMap::GetColour(index); }
};

}

#endif
