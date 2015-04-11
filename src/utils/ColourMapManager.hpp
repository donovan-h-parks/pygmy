//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _COLOUR_MAP_MANAGER_
#define _COLOUR_MAP_MANAGER_

namespace utils
{

/**
 * @class ColourMapManager
 * @brief Provides easy access to colour maps.
 */
class ColourMapManager
{
public:
	typedef std::map<std::wstring, ColourMapPtr>::const_iterator ColourMapConstIter;
	typedef std::pair<std::wstring, ColourMapPtr> ColourMapPair;

public:
	/** Constructor. */
	ColourMapManager() {}

	/** Destructor. */
	virtual ~ColourMapManager() {}

	/** Get colour map with the provided name. */
	ColourMapPtr GetColourMap(const std::wstring& name);

	/** Get default discrete colour map. */
	ColourMapPtr GetDefaultDiscreteMap();

	/** Get default continuous colour map. */
	ColourMapPtr GetDefaultContinuousMap();

	/** Get default categorical colour map. */
	ColourMapPtr GetDefaultCategoricalMap();

	/** 
	 * @brief Load all colour maps in a directory. 
	 * @param colorMapPath Path to directory containing predefined colour maps.
	 * @return True if colour maps loaded successfully, otherwise False.
	 */
	bool LoadColourMaps(const std::wstring& colorMapPath);

	/** Get all colour maps. */
	const std::map<std::wstring, ColourMapPtr>& GetMaps() const { return m_colourMaps; }

	/** Get categorical colour maps. */
	std::vector<std::wstring> GetCategoricalMaps() const;

	/** Get continuous colour maps. */
	std::vector<std::wstring> GetContinuousMaps() const;

	/** Get discrete colour maps. */
	std::vector<std::wstring> GetDiscreteMaps() const;

	/** Get last selected categorical colour map. */
	const std::wstring& GetLastSelectedCategorical();

	/** Get last selected continuous colour map. */
	const std::wstring& GetLastSelectedContinuous();

	/** Get last selected discrete colour map. */
	const std::wstring& GetLastSelectedDiscrete();

	/** Set last selected colour map. */
	void SetLastSelected(const std::wstring mapName);
	
protected:
	/** All supported colour maps. */
	std::map<std::wstring, ColourMapPtr> m_colourMaps;

	/** Last selected categorical colour map. */
	std::wstring m_lastCategoricalMap;

	/** Last selected continuous colour map. */
	std::wstring m_lastContinuousMap; 

	/** Last selected discrete colour map. */
	std::wstring m_lastDiscreteMap; 
};

}

#endif
