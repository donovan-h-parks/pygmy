//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _PYGMY_COMMON_
#define _PYGMY_COMMON_

#pragma message("*** Compiling Common.hpp: This should happen once on a full build if precompiled headers are setup properly. ***\n")

#include "../utils/Point.hpp"

namespace utils
{

//--- Common Data Structures --------------------------------------------------

/** Bounding Box. */
typedef struct sBOUNDING_BOX
{
	/** Constructor. */
	sBOUNDING_BOX(float _x = 0, float _y = 0, float _dx = 0, float _dy = 0): x(_x), y(_y), dx(_dx), dy(_dy) {}

	/** Width of box. */
	float Width() { return dx - x; }

	/** Height of box. */
	float Height() { return dy - y; }

	/** Lower, left x-coordinate of box. */
  float x;

	/** Lower, left y-coordinate of box. */
  float y;

	/** Upper, right x-coordinate of box. */
  float dx;

	/** Upper, right y-coordinate of box. */
  float dy;
} BBox;

/** Bounding Box. */
typedef struct sRECT
{
	/** Constructor. */
	sRECT(Point _ll = Point(), Point _ul = Point(), Point _ur = Point(), Point _lr = Point())
		: ll(_ll), ul(_ul), ur(_ur), lr(_lr) {}

	/** Lower, left coordinate of box. */
  Point ll;

	/** Upper, left coordinate of box. */
  Point ul;

	/** Upper, right coordinate of box. */
  Point ur;

	/** Upper, right coordinate of box. */
  Point lr;
} Rect;

/**
 * @brief Line interval.
 */
typedef struct sINTERVAL
{
	/** Constructor. */
	sINTERVAL(float _start = 0, float _end = 0) :start(_start), end(_end) {}

	/** Midpoint of the interval. */
	float MidPoint() { return (end - start) / 2 + start; }

	/** Start of interval. */
	float start;

	/** End of interval. */
	float end;
} Interval;

//--- Common macros

// Allows for more natural iteration over a sequence
#define foreach BOOST_FOREACH


//--- Common Numeric Values ---------------------------------------------------

#define PI 3.14159265f
#define PI2 (2*PI)
#define PI_BY_2 (PI / 2.0f)
#define EPSILON 0.00000001f
#define DEG_TO_RAD (PI/180.0f)
#define RAD_TO_DEG (180.0f/PI)
#define TAN_30	0.5773502692f
#define COS_30	0.8660254038f
#define SIN_30	0.5f
#define FLT_MAX std::numeric_limits<float>::max()
#define FLT_MIN -std::numeric_limits<float>::max()
#define DBL_MAX std::numeric_limits<double>::max()
#define DBL_MIN -std::numeric_limits<double>::max()

//--- Useful flags ---

#define NOT_SET INT_MAX

}

#endif
