//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/ColourMapDiscrete.hpp"
#include "../utils/Log.hpp"
#include "../utils/StringTools.hpp"

using namespace utils;

ColourMapDiscrete::ColourMapDiscrete(ColourMapPtr colourMap)
{
	m_colourMap.clear();
	for(uint i = 0; i < colourMap->GetSize(); ++i)
		m_colourMap.push_back(colourMap->GetColour(i));		

	m_name = colourMap->GetName();

	// Note: the type of a discrete colour map can be CONTINUOUS
	// as the type refers to the underlying colour map and how
	// colours should be obtained from it
	m_type = colourMap->GetType();
}

ColourMapDiscrete::ColourMapDiscrete(ColourMapDiscretePtr colourMap)
{
	CopyColourMap(colourMap);
}

void ColourMapDiscrete::CopyColourMap(ColourMapDiscretePtr colourMap)
{
	m_colourMap.clear();
	for(uint i = 0; i < colourMap->GetSize(); ++i)
		m_colourMap.push_back(colourMap->GetColour(i));		

	m_colourNames = colourMap->GetNameToColourMap();

	m_name = colourMap->GetName();

	// Note: the type of a discrete colour map can be CONTINUOUS
	// as the type refers to the underlying colour map and how
	// colours should be obtained from it
	m_type = colourMap->GetType();
}

void ColourMapDiscrete::SetColour(const std::wstring& name, const Colour& colour) 
{ 
	std::map<std::wstring, Colour>::iterator it = m_colourNames.find(name);
	if(it != m_colourNames.end())
	{
		it->second = colour;
	}
	else
	{
		m_colourNames[name] = colour;
	}
}

bool ColourMapDiscrete::GetColour(const std::wstring& name, Colour& colour) const
{
	std::map<std::wstring, Colour>::const_iterator it = m_colourNames.find(name);
	if(it == m_colourNames.end())
	{
		colour = ColourMap::GetDefaultColour();
		return false;
	}

	colour = it->second;

	return true;
}
