//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/AlphaNumericSorter.hpp"
#include "../utils/StringTools.hpp"

using namespace utils;
using namespace std;

/** Structure used to sort numerical strings. */
typedef struct sNUMERIC_STRING_SORTER
{
	sNUMERIC_STRING_SORTER(double _numericStr, uint _index): numericStr(_numericStr), index(_index) {}

	static bool NumericStringPredicate(sNUMERIC_STRING_SORTER elem1, sNUMERIC_STRING_SORTER elem2)
	{
		 return elem1.numericStr < elem2.numericStr;
	}

	double numericStr;
	uint index;
} NumericStringSorter;


void AlphaNumericSorter::Sort(std::vector<std::wstring>& values)
{
	// if all data is numerical, than sort in numerical as opposed to lexigraphical order
	bool bNumeric = true;
	foreach(std::wstring str, values)
	{
		if(!utils::StringTools::IsDecimalNumber(str))
		{
			bNumeric = false;
			break;
		}
	}

	// sort field values eith numerically or lexigraphically
	if(bNumeric)
	{
		// convert all data to its numeric equivalent, sort, and put back into string vector
		// Note: this somewhate convoluted way of doing a numerical sort of strings is done to
		// ensure that at the end the field values strings are exactly as they originally appeared.
		// Any added training zeros or rounding may cause problems later on when exact string matching
		// is attempted.
		std::vector<NumericStringSorter> fieldNumeric;
		for(uint i = 0; i < values.size(); ++i)
		{
			fieldNumeric.push_back(NumericStringSorter(utils::StringTools::ToDouble(values.at(i)), i));
		}

		std::sort(fieldNumeric.begin(), fieldNumeric.end(), NumericStringSorter::NumericStringPredicate); 

		std::vector<std::wstring> sortedFieldValues;
		foreach(NumericStringSorter numeric, fieldNumeric)
		{
			sortedFieldValues.push_back(values.at(numeric.index));
		}

		values = sortedFieldValues;
	}
	else
	{
		// sort in lexigraphical order
		std::sort(values.begin(), values.end());
	}
}