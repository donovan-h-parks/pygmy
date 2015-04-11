//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _COLOUR_MAP_
#define _COLOUR_MAP_

#include "../core/Precompiled.hpp"

#include "../utils/Colour.hpp"

namespace utils
{

/**
 * @class ColourMap
 * @brief Stores a set of colours that can be access by index or name.
 */
class ColourMap
{
public:
	/** Different types of colour maps. */
	enum TYPE { UNKNOWN, CATEGORICAL, CONTINUOUS, DISCRETE };

public:
	/** Constructor. */
	ColourMap(const std::wstring& name = _T("<no name>"), TYPE type = UNKNOWN): m_name(name), m_type(type), m_bCustom(false) {}

	/** Constructor. */
	ColourMap(ColourMapPtr colourMap);

	/** Destructor. */
	virtual ~ColourMap() {}

	/** Set colour to assign by default. */
	static void SetDefaultColour(const Colour& colour) { m_defaultColour = colour; }

	/** Get default colour. */
	static Colour GetDefaultColour() { return m_defaultColour; }

	/** Add colour to colour map. */
	virtual void AddColour(const Colour& colour) { m_colourMap.push_back(colour); }

	/** Set colour of colour map at a given index. */
	virtual void SetColour(const Colour& colour, uint index);

	/** Get colour from colour map. */
	Colour GetColour(uint index) const;

	/** Set name of colour map. */
	void SetName(const std::wstring& name) { m_name = name; }
  
	/** Get name of colour map. */
	const std::wstring& GetName() const { return m_name; }

  /** Get the size of the colour map. */
  uint GetSize() const;
  
	/** Set type of colour map. */
	void SetType(TYPE type) { m_type = type; }

	/** Get type of colour map. */
	TYPE GetType() const { return m_type; }

	/** 
	 * @brief Copy colour map. 
	 * @param colourMap Colour map to copy colours from.
	 */
	virtual void CopyColourMap(ColourMapPtr colourMap);

	/** 
	 * @brief Read type information from a colour map file.
	 * @param filename Filename (including path) of colour map to read.
	 * @return Type of colour map.
	 */
	TYPE ReadType(const std::wstring& filename);

	/** 
	 * @brief Load colour map from file. 
	 * @param filename Filename (including path) of colour map to load.
	 * @return True if colour maps loaded successfully, otherwise False.
	 */
	bool Load(const std::wstring& filename);

	/** Determine if colour map has been modified (i.e., is a custom colour map). */
	bool IsCustom() const { return m_bCustom; }

	/** Set colour map as being custom or predefined. */
	void SetCustom(bool custom);
	
protected:
	/** Colour map. */
	std::vector<Colour> m_colourMap;

	/** Name of colour map. */
	std::wstring m_name;

	/** Type of colour map. */
	TYPE m_type;

	/** Flag indicating if colour map is custom. */
	bool m_bCustom;

	/** Default colour. */
	static Colour m_defaultColour;
};

}

#endif
