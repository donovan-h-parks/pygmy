//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _STRINGTOOLS_H_
#define _STRINGTOOLS_H_

#include "../core/Precompiled.hpp"

namespace utils
{

/**
 * @brief Some utilitary functions that work on strings.
 */
class StringTools
{
public:

	/**
	 * @brief Tell if a std::wstring is empty.
	 *
	 * A std::wstring is considered to be 'empty' if it is only made of white spaces.
	 *
	 * @param s The std::wstring to check.
	 * @return True if the std::wstring has only white character.
	 */
	static bool IsEmpty(const std::wstring & s);

	/**
	 * @brief Tell if a std::wstring is an integer number.
	 *
	 * @param s The std::wstring to check.
	 * @return True if the std::wstring is an integer number.
	 */
	static bool IsInteger(const std::wstring & s) { return boost::all(s, boost::is_digit()); }

	/**
	 * @brief Tell if a std::wstring is a decimal number.
	 *
	 * @param s The std::wstring to check.
	 * @return True if the std::wstring is an decimal number.
	 */
	static bool IsDecimalNumber(const std::wstring & s);

	/**
	 * @brief Tell if a std::wstring is an integer number.
	 *
	 * @param s The std::wstring to check.
	 * @return True if the std::wstring is an integer number.
	 */
	static bool IsIntegerNumber(const std::wstring & s);

	/**
	 * @brief Make the std::wstring uppercase.
	 *
	 * @param s The std::wstring to analyse.
	 * @return The std::wstring with all wchar_ts changed to uppercase.
	 */
	static std::wstring ToUpper(const std::wstring & s);

	/**
	 * @brief Make the std::wstring lowercase.
	 *
	 * @param s The std::wstring to analyse.
	 * @return The std::wstring with all wchar_ts changed to lowercase.
	 */
	static std::wstring ToLower(const std::wstring & s);

	/**
	 * @brief Tell if a character is a white space or not.
	 *
	 * @param c The character to check.
	 * @return True if c is one of the following: ' ', '\\t', '\\n', '\\r' or '\\f'.
	 */
	static bool IsWhiteSpaceCharacter(wchar_t c);

	/**
	 * @brief Remove all white spaces characters in a std::wstring.
	 *
	 * @param s The std::wstring to parse.
	 * @return A copy of 's' without white spaces character.
	 */
	static std::wstring RemoveWhiteSpaces (const std::wstring & s);

	/**
	 * @brief Remove all white spaces characters at the beginning of a std::wstring.
	 *
	 * @param s The std::wstring to parse.
	 * @return The std::wstring beginning with the first non-white character.
	 */
	static std::wstring RemoveFirstWhiteSpaces (const std::wstring & s);

	/**
	 * @brief Remove all white spaces characters at the end of a std::wstring.
	 *
	 * @param s The std::wstring to parse.
	 * @return The std::wstring ending with the last non-white character.
	 */
	static std::wstring RemoveLastWhiteSpaces (const std::wstring & s);

	/**
	 * @brief Remove all white spaces characters at the beginning and the
	 * end of a std::wstring.
	 *
	 * @param s The std::wstring to parse.
	 * @return The std::wstring beginning with the first non-white character
	 * and ending with the last one.
	 */
	static std::wstring RemoveSurroundingWhiteSpaces(const std::wstring & s);

	/**
   * @brief Extract path and filename from string containing a full path.
   *
   * @param fullPath std::wstring containing full path to a file.
   * @param path std::wstring that will contain the path.
	 * @param filename std::wstring that will contain the filename.
   */
	static void ExtractPathAndFilename(const std::wstring& fullpath, std::wstring& path, std::wstring& filename);

  /**
   * @brief General template method to convert to a std::wstring.
   *
   * @param t The object to convert.
   * @return A std::wstring equal to t.
   */
  template<class T> static std::wstring ToString(T t)
	{
		std::wostringstream oss;
    oss << t;
    return oss.str();
  }

	/**
	 * @brief Template std::wstring conversion.
	 * 
	 * @param t The object to convert.
	 * @param precision To use (for numbers).
	 * @return A std::wstring equal to t.
	 */
	template<class T>
	static std::wstring ToString(T t, int precision)
	{
		std::wostringstream oss;
		oss << std::setprecision(precision) << t;
		return oss.str();
	}

  /**
   * @brief General template method to convert from std::wstring.
   *
   * @param s The std::wstring to convert.
   * @return An object from std::wstring t.
   */
  template<class T> static T FromString(const std::wstring & s)
	{
    std::istringstream iss(s);
    T obj;
    iss >> obj;
    return obj;
  }

  /**
	 * @brief Convert from int to std::wstring.
	 *
	 * @param i The integer to convert.
	 * @return A std::wstring equal to i.
	 */
	static std::wstring ToString(int i);

  /**
	 * @brief Convert from wchar_t to std::wstring.
	 *
	 * @param c The character to convert.
	 * @return A std::wstring equal to c.
	 */
	static std::wstring ToString(wchar_t c);

	/**
	 * @brief Convert from float to std::wstring.
	 *
	 * @param d The float to convert.
	 * @param precision To use (for numbers).
	 * @param bScientific Flag indicating if number should be formated as scientific or fixed.
	 * @return A std::wstring equal to d.
	 */
	static std::wstring ToString(float d, int precision = 6, bool bScientific = false);

		/**
	 * @brief Format a number string.
	 *
	 * @param s The std::wstring to format.
	 * @param precision To use (for numbers).
	 * @param bScientific Flag indicating if number should be formated as scientific or fixed.
	 * @return A std::wstring format as specified if the string is a number or the unaltered string if it was not a number.
	 */
	static std::wstring FormatNumberStr(const std::wstring &  s, int precision = 6, bool bScientific = false);

	/**
	 * @brief Convert from std::wstring to int.
	 *
	 * @param s The std::wstring to parse.
	 * @return The integer corresponding to s.
	 */
	static int ToInt(const std::wstring & s);

	/**
	 * @brief Convert from std::wstring to float.
	 *
	 * @param s The std::wstring to parse.
	 * @return The float corresponding to s.
	 */
	static float ToFloat(const std::wstring & s);

	/**
	 * @brief Convert from std::wstring to double.
	 *
	 * @param s The std::wstring to parse.
	 * @return The double corresponding to s.
	 */
	static double ToDouble(const std::wstring & s);

	/**
	 * @brief Convert from std::wstring to long.
	 *
	 * @param s The std::wstring to parse.
	 * @return The long corresponding to s.
	 */
	static long ToLong(const std::wstring & s);

	/**
	 * @brief Template to std::wstring conversion.
	 * 
	 * @param s The std::wstring to parse.
	 * @return An object of class R corresponding to s.
	 */
	template<class T>
	static T To(const std::wstring & s)
	{
		std::istringstream iss(s);
		T t;
		iss >> t;
		return t;
	}

	/**
	 * @brief Send a std::wstring of size 'newSize', which is a copy of 's' truncated or
	 * filled with character 'fill' at the end.
	 *
	 * @param s       The std::wstring to parse.
	 * @param newSize The new std::wstring size.
	 * @param fill    The character to use to fill the std::wstring id length < newSize.
	 * @return A std::wstring of size newsize which is a copy from the left of s.
	 */
	static std::wstring ResizeRight(const std::wstring & s, uint newSize, wchar_t fill = ' ');

	/**
	 * @brief Send a std::wstring of size 'newSize', which is a copy of 's' truncated or
	 * filled with character 'fill' at the beginning.
	 *
	 * @param s       The std::wstring to parse.
	 * @param newSize The new std::wstring size.
	 * @param fill    The character to use to fill the std::wstring id length < newSize.
	 * @return A std::wstring of size newsize which is a copy from the right of s.
	 */
	static std::wstring ResizeLeft(const std::wstring & s, uint newSize, wchar_t fill = ' ');

	/**
	 * @brief Split a std::wstring into parts of size 'n'.
	 *
	 * The last part may contain < n wchar_ts.
	 *
	 * @param s The std::wstring to parse.
	 * @param n The number of tokens.
	 * @return A vector of strings with all tokens.
	 */
	static std::vector<std::wstring> Split(const std::wstring & s, uint n);

	/**
	 * @brief Remove substrings from a std::wstring.
	 *
	 * All substrings beginning with blockBeginning
	 * and ending with blockEnding will be removed.
	 * Nesting blocks are allowed, the most extern block will be removed.
	 *
	 * @param s The std::wstring to parse.
	 * @param blockBeginning The character specifying the beginning of each block.
	 * @param blockEnding    The character specifying the end of each block.
	 * @return The std::wstring with all blocks removed.
	 */
	static std::wstring RemoveSubstrings(const std::wstring & s, wchar_t blockBeginning, wchar_t blockEnding);

  /**
   * @brief Remove all occurences of a character in a std::wstring.
   *
   * @param s The std::wstring to parse.
   * @param c The character to remove.
   * @return The std::wstring with all specified wchar_ts removed.
   */
  static std::wstring RemoveChar(const std::wstring & s, wchar_t c);

	/**
   * @brief Replace all occurences of a character in a std::wstring with another character.
   *
   * @param s The std::wstring to parse.
   * @param c The character to replace.
	 * @param r The replacement character.
   * @return The std::wstring with all specified wchar_ts removed.
   */
  static std::wstring ReplaceChar(const std::wstring & s, wchar_t c, wchar_t r);

  /**
   * @brief Count the occurences of a given pattern in a std::wstring.
   *
   * @param s The std::wstring to search.
   * @param pattern The pattern to use.
   * @return The number of occurences of 'pattern' in 's'.
   */
  static uint Count(const std::wstring & s, const std::wstring & pattern);
};

}


#endif

