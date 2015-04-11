//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/ColourMap.hpp"
#include "../utils/Log.hpp"
#include "../utils/StringTools.hpp"

using namespace utils;

Colour ColourMap::m_defaultColour = Colour(0,0,0);

ColourMap::ColourMap(ColourMapPtr colourMap)
{
	CopyColourMap(colourMap);
}

void ColourMap::CopyColourMap(ColourMapPtr colourMap)
{
	m_colourMap.clear();

	m_type = colourMap->GetType();
	m_name = colourMap->GetName();

	for(uint i = 0; i < colourMap->GetSize(); ++i)
		m_colourMap.push_back(colourMap->GetColour(i));
}

void ColourMap::SetColour(const Colour& colour, uint index)
{
	if(index >= m_colourMap.size())
		m_colourMap.resize(index+1, ColourMap::GetDefaultColour());

	m_colourMap.at(index) = colour;
}

Colour ColourMap::GetColour(uint index) const
{ 
	if(index < m_colourMap.size())
	{
		return m_colourMap.at(index);
	}

	return ColourMap::GetDefaultColour();
}

uint ColourMap::GetSize() const
{
  return m_colourMap.size();
}

ColourMap::TYPE ColourMap::ReadType(const std::wstring& filename)
{
	std::wifstream file(filename.c_str());
	if(!file)
	{
		utils::Log::Inst().Error(_T("(Error) ColourMap::ReadType(): invalid colour map file."));
		return UNKNOWN;
	}

	const uint DATA_SIZE = 256;
	wchar_t data[DATA_SIZE];
	std::wstring dataStr;

	// read type of colour map
	file.getline(data, DATA_SIZE);
	dataStr = data;
	uint pos = dataStr.find(_T(":"));	
	std::wstring type = dataStr.substr(pos+1);
	type = utils::StringTools::RemoveSurroundingWhiteSpaces(type);
	if(type == _T("DISCRETE"))
		return DISCRETE;
	else if(type == _T("CONTINUOUS"))
		return CONTINUOUS;
	else if(type == _T("CATEGORICAL"))
		return CATEGORICAL;

	return UNKNOWN;
}


bool ColourMap::Load(const std::wstring& filename)
{
	std::wifstream file(filename.c_str());
	if(!file)
		return false;

	const uint DATA_SIZE = 256;
	wchar_t data[DATA_SIZE];
	std::wstring dataStr;

	// read type of colour map
	file.getline(data, DATA_SIZE);
	dataStr = data;
	uint pos = dataStr.find(_T(":"));	
	std::wstring type = dataStr.substr(pos+1);
	type = utils::StringTools::RemoveSurroundingWhiteSpaces(type);
	if(type == _T("DISCRETE"))
		m_type = DISCRETE;
	else if(type == _T("CONTINUOUS"))
		m_type = CONTINUOUS;
	else if(type == _T("CATEGORICAL"))
		m_type = CATEGORICAL;

	// read name of colour map
	file.getline(data, DATA_SIZE);
	dataStr = data;
	pos = dataStr.find(_T(":"));	
	m_name = dataStr.substr(pos+1);
	m_name = utils::StringTools::RemoveSurroundingWhiteSpaces(m_name);

	// read number of colours in colour map
	file.getline(data, DATA_SIZE);
	dataStr = data;
	pos = dataStr.find(_T(":"));	
	std::wstring numColoursStr = dataStr.substr(pos+1);
	uint numColours = utils::StringTools::ToInt(utils::StringTools::RemoveSurroundingWhiteSpaces(numColoursStr));

	// read in colours
	int red, green, blue;
	for(uint i = 0; i < numColours; ++i)
	{
		file >> red >> green >> blue;
		m_colourMap.push_back(Colour(red, green, blue));
	}

	return true;
}

void ColourMap::SetCustom(bool custom) 
{ 
	m_bCustom = custom;
	m_type = DISCRETE;

	if(m_bCustom)
		m_name = _T("Custom");
}
