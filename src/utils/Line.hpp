//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _LINE_HPP_
#define _LINE_HPP_

#include "../core/Precompiled.hpp"

#include "../utils/Point.hpp"

namespace utils
{

/**
 * @brief General 2D line.
 */
class Line
{
public:
	/** Default constructor. */
	Line(): start(Point(0,0)), end(Point(0,0)) {}

	/** Constructor. */
	Line(const Point& _start, const Point& _end): start(_start), end(_end) {}

	/** Desturctor. */
	~Line() {}

	/** Length of line. */
	float Length() const { return (start-end).Length(); }

public:
	/** Unary negation. */
	const Line operator-() const { return Line(end, start); }

	/** Equality operator. */
	bool operator==(const Line& line) const { return (start == line.start && end == line.end); }

	/** Not equal operator. */
	bool operator!=(const Line& line) const { return !(*this == line); }

public:
	/** Start of line. */
	Point start;

	/** End of line. */
  Point end;
};

}

#endif
