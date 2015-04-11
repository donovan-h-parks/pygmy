//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/Point.hpp"

using namespace utils;

const Point&  Point::Normalize() 
{                     
	float len = Length();
	if (len == 0) 
		return *this; 

	x /= len;
	y /= len;

	return *this;
}

Point Point::Offset(const Point& pt) const
{
	Point offsetPt;
	offsetPt.x = x + pt.x;
	offsetPt.y = y + pt.y;

	return offsetPt;
}

float Point::Cross(const Point& pt) const
{
	return x * pt.y - y * pt.x;
}

float Point::Angle(const Point& pt) const
{
	float len = Length();
	float len2 = pt.Length();

	if(len == 0 || len2 == 0)
		return 0.0;

	float dp = (x * pt.x + y * pt.y) / (len * len2);
	if (dp >= 1.0) 
		return 0.0f;
  
	if (dp <= -1.0f) 
		return 3.14159265f;

	return acos(dp);
}
