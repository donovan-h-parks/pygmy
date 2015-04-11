//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _ERROR_H_
#define _ERROR_H_

//#include <cassert>

namespace utils
{

/**
 * @brief Error handling functions.
 */
class Error
{
public:
	/**
	 * @brief Assert that a boolean expression is true.
	 * @param b Results of expression.
	 */
	static void Assert(bool b)
	{
		#ifndef NDEBUG
			if(!b)
			{
				// placing a break point on this line allows rapid debugging of failed assert statements
				assert(b);
			}
		#endif
	}
};

}

#endif