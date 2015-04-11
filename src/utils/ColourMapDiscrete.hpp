//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _COLOUR_MAP_DISCRETE_
#define _COLOUR_MAP_DISCRETE_

#include "../utils/ColourMap.hpp"

#include "../utils/Colour.hpp"

namespace utils
{

/**
 * @class ColourMapDiscrete
 * @brief Stores a set of colours that can be access by name.
 */
class ColourMapDiscrete: public ColourMap
{
public:
	/** Constructor. */
	ColourMapDiscrete(): ColourMap(_T("<no name>"), DISCRETE) {}

	/** Constructor. */
	ColourMapDiscrete(const std::wstring& name, TYPE type = DISCRETE): ColourMap(name, type) {}

	/** Constructor. */
	ColourMapDiscrete(ColourMapPtr colourMap);

	/** Constructor. */
	ColourMapDiscrete(ColourMapDiscretePtr colourMap);

	/** Destructor. */
	virtual ~ColourMapDiscrete() {}

	/** 
	 * @brief Copy colour map. 
	 * @param colourMap Colour map to copy colours from.
	 */
	void CopyColourMap(ColourMapDiscretePtr colourMap);

	/** 
	 * @brief Copy colour map. 
	 * @param colourMap Colour map to copy colours from.
	 */
	void CopyColourMap(ColourMapPtr colourMap) { ColourMap::CopyColourMap(colourMap); }

	/** 
	 * @brief Assign colour to a given index and name. 
	 * @param name Name to associate with this colour.
	 * @param colour Desired colour.
	 */
	void SetColour(const std::wstring& name, const Colour& colour);

	/** Set colour of colour map at a given index. */
	void SetColour(const Colour& colour, uint index) { ColourMap::SetColour(colour, index); }

	/** Get colour associated with the given name. */
	bool GetColour(const std::wstring& name, Colour& colour) const;

	/** Get colour from underlying colour map. */
	Colour GetColour(uint index) const { return ColourMap::GetColour(index); }

	/** Clear names associated with colours. */
	void ClearNames() { m_colourNames.clear(); }

	/** Get map which associates names with colour. */
	std::map<std::wstring, Colour> GetNameToColourMap() { return m_colourNames; }

	/** Get size of map which associates names to colours. */
	uint GetNameToColourMapSize() { return m_colourNames.size(); }

protected:
	/** Name associated with each colour. */
	std::map<std::wstring, Colour> m_colourNames;
};

}

#endif
