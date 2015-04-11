//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/ColourMapContinuous.hpp"
#include "../utils/Log.hpp"
#include "../utils/StringTools.hpp"

using namespace utils;

Colour ColourMapContinuous::GetColour(float value, float minValue, float maxValue) const
{
	if(maxValue == minValue)
	{
		return m_colourMap.at(0);
	}

	// determine offset of desired colour between [0, 1]
	float delta = (value - minValue) / (maxValue - minValue);

	// determine colour "bin" to interpolate colour over
	float binSize = 1.0 / (m_colourMap.size()-1);
	uint binIndex = floor(delta / binSize);
	if(value == maxValue)
	{
		// degenerate case that doesn't work with above formula
		binIndex = m_colourMap.size()-2;
	}

	// interpolate colour over colour bin
	delta = (delta - binIndex*binSize) / binSize;
	Colour startColour = m_colourMap.at(binIndex);
	Colour endColour = m_colourMap.at(binIndex+1);
	float red = startColour.GetRed() + (endColour.GetRed()-startColour.GetRed())*delta;
	float green = startColour.GetGreen() + (endColour.GetGreen()-startColour.GetGreen())*delta;
	float blue = startColour.GetBlue() + (endColour.GetBlue()-startColour.GetBlue())*delta;

	return Colour(red, green, blue, 1.0f);
}