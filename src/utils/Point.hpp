//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _POINT_HPP_
#define _POINT_HPP_

#include "../core/Precompiled.hpp"

namespace utils
{

/**
 * @brief General 2D point. Also used as a vector depending on context.
 */
class Point
{
public:
	/** Constructor. */
	Point(float _x = 0, float _y = 0): x(_x), y(_y) {}

	/** Desturctor. */
	~Point() {}

	/**
	 * @brief Calculate a point this is offset from this one.
	 * @param offset Point, P, indicate amount to offset in each direction.
	 * @return New point the is offset from this one by the amount specified in P.
	 */
	Point Offset(const Point& pt) const;

	/** Length of point (vector). */
	float Length() const { return sqrt(SquaredLength()); }

	/** Squared length of point (vector). */
	float SquaredLength() const { return (x*x + y*y); }

	/** Normalize point (vector> to unit length. */
	const Point& Normalize();

	/** Cross product between vectors. */
	float Cross(const Point& pt) const;

	/** Orthogonal vector (can be seen as another analog of a 3D cross product). */
	Point OthogonalVector() { return Point(y, -x); }

	/** Dot product. Can also use * operator. */
	double Dot(const Point& pt) const { return x * pt.x + y * pt.y; }

	/** Calculate the smallest angle between two vectors. */
	float Angle(const Point& pt) const;

public:
	/** Compound addition operator. */
	Point& operator+=(const Point& pt)
	{
		x += pt.x;
		y += pt.y;
		return *this;
  }

	/** Compound subtraction operator. */
	Point& operator-=(const Point& pt)
	{
		x -= pt.x;
		y -= pt.y;
		return *this;
  }

	/** Add two points. */
  const Point operator+(const Point& pt) const { return Point(x + pt.x, y + pt.y); }
  
	/** Subtract two points. */
	const Point operator-(const Point& pt) const { return Point(x - pt.x, y - pt.y); }

	/** Inner dot product. */
	const float operator*(const Point& pt) const { return x * pt.x + y * pt.y; }

	/** Scalar multiplication. */
	friend Point operator*(float c, Point pt) { return Point(c*pt.x, c*pt.y); }
	
	/** Scalar multiplication. */
	friend Point operator*(const Point& pt, float c) { return Point(c*pt.x, c*pt.y); }

	/** Scalar division. */
	friend Point operator/(const Point& pt, float c) { return Point(pt.x/c, pt.y/c); }

	/** Unary negation. */
	const Point operator-() const { return Point(-x, -y); }

	/** Equality operator. */
	bool operator==(const Point& pt) const { return (x==pt.x && y==pt.y); }


	/** Not equal operator. */
	bool operator!=(const Point& pt) const { return !(*this == pt); }

public:
	/** x position of point. */
	float x;

	/** y position of point. */
  float y;
};

}

#endif
