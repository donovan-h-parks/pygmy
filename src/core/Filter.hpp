//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _FILTER_H_
#define _FILTER_H_

#include "../core/Precompiled.hpp"

#include "../core/NodePhylo.hpp"

#include "../utils/Colour.hpp"

#include <set>

namespace pygmy
{

/**
 * @brief Maintain a list of filtered nodes and how they should
 *				by visualized.
 */
class Filter
{
public:
	/** Clear the filter list. */
	void Clear() { m_ids.clear(); }

	/**
	 * @brief Add an item to the list.
	 */
	void Add(uint id) { m_ids.insert(id); }

	/** Filter colour. */
	void SetColour(const utils::Colour& colour) { m_colour = colour; }

	/** Filter colour (read-only). */
	const utils::Colour& GetColour() const { return m_colour; }

	/** Check if an item is in the filter list. */
	bool Filtered(uint id) { return (m_ids.find(id) != m_ids.end()); }

	/** Get the filitered list. */
	std::set<uint> FilteredList() { return m_ids; }

private:
	/** Vector of filtered nodes. */
	std::set<uint> m_ids;

	/** Colour of the filitered nodes. */
	utils::Colour m_colour;
};

}

#endif

