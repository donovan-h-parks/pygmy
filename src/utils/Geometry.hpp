//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../core/Precompiled.hpp"

#include "../utils/Point.hpp"
#include "../utils/Line.hpp"

namespace utils
{

/**
 * @brief Functions for calculating basic geometric relationships.
 */
class Geometry
{
public:
	/**
	 * @brief Find intersection between a vertical and diagonal line.
	 * @param line Diagonal line.
	 * @param x X-coordinate of vertical line.
	 * @return Point of intersections.
	 * @throw ZeroDivisionException If a division by zero occurs.
	 */
	static Point VerticalIntersect(const Line& line, const double x);

	/**
	 * @brief Find intersection between a horizontal and diagonal line.
	 * @param line Diagonal line.
	 * @param y Y-coordinate of horizontal line.
	 * @return Point of intersections.
	 * @throw ZeroDivisionException If a division by zero occurs.
	 */
	static Point HorizontalIntersect(const Line& line, const double y);

	/**
	 * @brief Find intersection between two lines.
	 * @param line Diagonal line 1.
	 * @param line Diagonal line 2.
	 * @return Point of intersections between lines.
	 */
	static Point Intersect(const Line& line1, const Line& line2);

	/**
	 * @brief Find the closest point on a line, L, to a given point, P.
	 * @param line Line L.
	 * @param point Point P.
	 * @param closestPoint Set to the closest point on L to P.
	 * @return True if closest point on the line is on the line segment specified by L, otherwise false.
	 */
	static bool ClosestPointToLine(const Line& line, const Point& point, Point& closestPoint);

	/**
	 * @brief Calculate the distance between two points.
	 * @param pt1 First point.
	 * @param pt2 Second point.
	 * @return Distance between points.
	 */
	static double Distance(const Point& pt1, const Point& pt2);

	/**
	 * @brief Calculate length of line
	 * @param line Line to calculate length of
	 * @return Distance between end points of line.
	 */
	static double LineLength(const Line& line) { return Distance(line.start, line.end); }

	/**
	 * @brief Signed angle between given line and x-axis. Positive angles are CCW.
	 * @param line Line of interest. 
	 * @return Signed angle (between -PI and PI).
	 */
	static double AngleToX(const Line& line);

	/** 
	 * @brief Find mid-point of a line.
	 * @param line Line of interest.
	 * @return Mid-point of line.
	 */
	static Point MidPoint(const Line& line);

	/**
	 * @brief Normal to line. The normal is on the RHS as one goes from the start to end points of the line. 
	 * @param line Line of interest. 
	 * @return Normal to line.
	 */
	static Point NormalToLine(const Line& line);

	/**
	 * @brief Determine if a point is within a triangle. 
	 * @param pt Point to test.
	 * @param x1 First vertex of triangle.
	 * @param x2 Second vertex of triangle.
	 * @param x3 Thrid vertex of triangle.
	 * @return True if the point is contained in the triangle.
	 */
	static bool PointInTriangle(const Point& pt, const Point& v1, const Point& v2, const Point& v3);

	/**
	 * @brief Determine if a point is within a polygon.
	 * @param pt Point to test.
	 * @param polygon Vector of points defining polygon. All points should be specified only once.
	 * @return True if the point is contained in the polygon.
	 */
	static bool PointInPolygon(const Point& pt, const std::vector<Point>& polygon);

	/**
	 * @brief Determine signed angle between two vectors.
	 * @param origin Origin of vectors.
	 * @param p1 End of vector 1.
	 * @param p2 End of vector 2.
	 * @return Signed angle (ie. 0 to PI or -PI) between vectors.
	 */
	static double SignedAngle(const Point& origin, const Point& p1, const Point& p2);

	/**
	 * @brief Determine closest point on ellipse to a given point.
	 * @param pt Point of interest.
	 * @param xRadius Radius of ellipse along x-axis.
	 * @param yRadius Radius of ellipse along y-axis.
	 * @param dEpsilon Tolerance for Newton's method.
	 * @param iMax Maximum number of iterations of Newton's method to perform.
	 * @param iFinal Number of iterations of Newton's method performed.
	 * @param closestX X-coordinate of closest point on ellipse to the given point.
	 * @param closestY y-coordinate of closest point on ellipse to the given point.
	 * @return Distance from given point and closest point on ellipse.
	 */
	static double DistancePointEllipse(Point& pt, double xRadius, double yRadius,
																					const double dEpsilon, const int iMax, int& iFinal, double& closestX, double& closestY);

	/**
	 * @brief Determine intersection between an ellipse and line extending from the ellipse origin. 
	 * @param xRadius Radius of ellipse along x-axis.
	 * @param yRadius Radius of ellipse along y-axis.
	 * @param lineEnd End point of line.
	 * @return Intersection point.
	 */
	static Point EllipseOriginLineIntersect(double xRadius, double yRadius, Point& lineEnd);

	/**
	 * @brief Determine point on ellipse at a given angle.
	 * @param xRadius Radius of ellipse along x-axis.
	 * @param yRadius Radius of ellipse along y-axis.
	 * @param angle Angle from x-axis.
	 * @return Point on ellipse at given angle.
	 */
	static Point GetEllipsePointAtAngle(double xRadius, double yRadius, double angle);

	/**
	 * @brief Find intersection between an ellipse and a line. 
	 * @param xRadius Radius of ellipse along x-axis.
	 * @param yRadius Radius of ellipse along y-axis.
	 * @param line Line to find intersection with.
	 * @param intersectPts Intersection point between line and ellipse (may be 0, 1, or 2 points).
	 * @return True if there is 1 or more intersection points.
	 */
	static bool EllipseLineIntersect(double xRadius, double yRadius, Line& line, std::vector<Point>& intersectPts);

	/**
	 * @brief Determine normal vector at a given point to an ellipse in standard position. 
	 * @param xRadius Radius of ellipse along x-axis.
	 * @param yRadius Radius of ellipse along y-axis.
	 * @param pt Point to determine tangent at.
	 * @return Vector indicating tangent direction at the given point.
	 */
	static Point EllipseNormal(double xRadius, double yyRadius, const Point& canonicalPt);

	/** 
	 * @brief Determine if the smallest angle between a start and stop angle is in the CW or CCW direction.
	 * @param start First angle of interest.
	 * @param end Second angle of interest.
	 * @return -1/1 if the smallest angle going from start to end is in the CW/CCW direction.
	 */
	 static int SmallestAngleDir(double start, double end);

	 	/** 
	 * @brief Find angle bisector of two angles.
	 * @param angle1 First angle.
	 * @param angle2 Second angle.
	 * @return Angle halfway between angle1 and angle2.
	 */
	static double AngleBisector(double angle1, double angle2);

	 /**
	  * @brief Find the angle bisector of a set of angles. For set with more
		*					than 2 angles, the largest angle between any two adjacent angles is identified.
		*					The angle bisector is than set half-way between these two angles such that it 
		*					is in the "middle" of the other angles.
		* @param angles Angles to find mid-point of (all angles must be between 0 and 2PI)
		* @param ccwAngles Order indices going in CCW order from the two angles used to calculate the bisector.
		* @return Angle bisector of set of angles.
		*/
	 static double AngleBisector(std::vector<double> angles, std::vector<uint>& ccwIndices);

private:
	/**
	 * @brief Helper function for determine closest point on ellipse to a given point. 
	 * @param pt Point of interest.
	 * @param xRadius Radius of ellipse along x-axis.
	 * @param yRadius Radius of ellipse along y-axis.
	 * @param dEpsilon Tolerance for Newton's method.
	 * @param iMax Maximum number of iterations of Newton's method to perform.
	 * @param iFinal Number of iterations of Newton's method performed.
	 * @param closestX X-coordinate of closest point on ellipse to the given point.
	 * @param closestZ z-coordinate of closest point on ellipse to the given point.
	 * @return Distance from given point and closest point on ellipse.
	 */
	static double DistancePointEllipseSpecial(Point& pt, double xRadius, double yRadius,
																								const double dEpsilon, const int iMax, int& iFinal, double& closestX, double& closestZ);
};

}

#endif
