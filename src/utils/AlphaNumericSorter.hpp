//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _ALPHA_NUMERIC_SORTER_HPP_
#define _ALPHA_NUMERIC_SORTER_HPP_

#include "../core/Precompiled.hpp"

namespace utils
{

/**
 * @brief Static class for performing alphanumeric sorting.
 */
class AlphaNumericSorter
{
public:

	/** 
	 * @brief Sort field values either in lexigraphically or numerically. 
	 * @param values Vector of values to be sorted.
	 */
	static void Sort(std::vector<std::wstring>& values);
};

}


#endif

