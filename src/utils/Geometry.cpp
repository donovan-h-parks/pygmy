//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/Geometry.hpp"
#include "../utils/Error.hpp"

using namespace utils;

const double eps = 1e-6;

Point Geometry::VerticalIntersect(const Line& line, const double x)
{
	utils::Error::Assert((line.end.x-line.start.x) != 0);

	double slope = (line.end.y - line.start.y) / (line.end.x-line.start.x);
	double run = x - line.start.x;

	double yInter = line.start.y+slope*run;

	return Point((float)x, (float)yInter);
}

Point Geometry::HorizontalIntersect(const Line& line, const double y)
{
	if((line.end.y - line.start.y) == 0)
	{
		utils::Error::Assert((line.end.y - line.start.y) != 0);
	}

	double vertSlope = (line.end.x-line.start.x) / (line.end.y - line.start.y);
	double vertRun = y - line.start.y;

	double xInter = line.start.x+vertSlope*vertRun;

	return Point((float)xInter, (float)y);
}

Point Geometry::Intersect(const Line& line1, const Line& line2)
{
	// express line 1 in form: Ax+By=C
	double A1 = line1.end.y - line1.start.y;
	double B1 = line1.start.x - line1.end.x;
	double C1 = A1*line1.start.x + B1*line1.start.y;

	// express line 2 in form: Ax+By=C
	double A2 = line2.end.y - line2.start.y;
	double B2 = line2.start.x - line2.end.x;
	double C2 = A2*line2.start.x + B2*line2.start.y;

	double det = A1*B2 - A2*B1;
	if(det != 0)
	{
		double x = (B2*C1 - B1*C2)/det;
		double y = (A1*C2 - A2*C1)/det;

		return Point((float)x, (float)y);
	}

	return Point(0, 0);
}

bool Geometry::ClosestPointToLine(const Line& line, const Point& point, Point& closestPoint)
{
	/*
	[ Source unknown ]

	Subject 1.02: How do I find the distance from a point to a line?


			Let the point be C (Cx,Cy) and the line be AB (Ax,Ay) to (Bx,By).
			Let P be the point of perpendicular projection of C on AB.  The parameter
			r, which indicates P's position along AB, is computed by the dot product 
			of AC and AB divided by the square of the length of AB:
	    
			(1)     AC dot AB
					r = ---------  
							||AB||^2
	    
			r has the following meaning:
	    
					r=0      P = A
					r=1      P = B
					r<0      P is on the backward extension of AB
					r>1      P is on the forward extension of AB
					0<r<1    P is interior to AB
	*/

	double dx = line.end.x-line.start.x;
	double dy = line.end.y-line.start.y;

	double r_numerator = (point.x-line.start.x)*dx + (point.y-line.start.y)*dy;
	double r_denomenator = dx*dx + dy*dy;
	double r = r_numerator / r_denomenator;

	closestPoint.x = (float)(line.start.x + r*dx);
	closestPoint.y = (float)(line.start.y + r*dy);

	return (r >= 0 && r <= 1);
}

double Geometry::Distance(const Point& pt1, const Point& pt2)
{
	double dx = pt1.x - pt2.x;
	double dy = pt1.y - pt2.y;

	return sqrt(dx*dx + dy*dy);
}

double Geometry::AngleToX(const Line& line)
{
	Point vec = line.end - line.start;
	double angleToX = vec.Angle(Point(1, 0));
	if(vec.y < 0)
	{
		// Angle() returns the smallest angle between two vectors. if the line goes in 
		// the positive z direction than it is a CW angle so should be negative
		angleToX = -angleToX;
	}	

	return angleToX;
}

Point Geometry::MidPoint(const Line& line)
{	
	return line.start + 0.5*(line.end-line.start);
}

Point Geometry::NormalToLine(const Line& line)
{
	Point lineDir = (line.start - line.end);
	lineDir.Normalize();
	Point normDir = lineDir.OthogonalVector();
	normDir.Normalize();

	return normDir;
}

bool Geometry::PointInTriangle(const Point& pt, const Point& v1, const Point& v2, const Point& v3)
{
	Point vec1 = pt - v1;
	Point vec2 = pt - v2;
	Point vec3 = pt - v3;

	vec1.y = vec2.y = vec3.y = 0;

	double angle1 = vec1.Angle(vec2);
	double angle2 = vec2.Angle(vec3);
	double angle3 = vec3.Angle(vec1);

	double sum = angle1 + angle2 + angle3;

	return (sum > PI2-eps && sum < PI2+eps);
}

bool Geometry::PointInPolygon(const Point& pt, const std::vector<Point>& polygon)
{
	// Taken from: http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/
	// Uses the crossing number (even-odd rule) algorithm
  unsigned int i, j;
	bool bInPolygon = false;
  for(i = 0, j = polygon.size()-1; i < polygon.size(); j = i++) 
	{
    if ((((polygon.at(i).y <= pt.y) && (pt.y < polygon.at(j).y)) ||
         ((polygon.at(j).y <= pt.y) && (pt.y < polygon.at(i).y))) &&
        (pt.x < (polygon.at(j).x - polygon.at(i).x) * (pt.y - polygon.at(i).y) / (polygon.at(j).y - polygon.at(i).y) + polygon.at(i).x))
		{
      bInPolygon = !bInPolygon;
		}
  }

  return bInPolygon;
}

double Geometry::SignedAngle(const Point& origin, const Point& p1, const Point& p2)
{
	Point vec1 = p1 - origin;
	vec1.y = 0;
	vec1.Normalize();

	Point vec2 = p2 - origin;
	vec2.y = 0;
	vec2.Normalize();

	double dot = vec1.Dot(vec2);
	double perpDot = vec1.x * vec2.y - vec1.y * vec2.x;

	return atan2(perpDot, dot);
}



double Geometry::DistancePointEllipseSpecial(Point& pt, double xRadius, double yRadius,
																									const double dEpsilon, const int iMax, int& iFinal, 
																									double& closestX, double& closestZ)
{
	// http://www.geometrictools.com/Documentation/DistancePointToEllipse2.pdf

	// initial guess
	double dT = yRadius*(pt.y - yRadius);
	// Newton’s method
	int i;
	for (i = 0; i < iMax; i++)
	{
		double dTpASqr = dT + xRadius*xRadius;
		double dTpBSqr = dT + yRadius*yRadius;
		double dInvTpASqr = 1.0/dTpASqr;
		double dInvTpBSqr = 1.0/dTpBSqr;
		double dXDivA = xRadius*pt.x*dInvTpASqr;
		double dYDivB = yRadius*pt.y*dInvTpBSqr;
		double dXDivASqr = dXDivA*dXDivA;
		double dYDivBSqr = dYDivB*dYDivB;
		double dF = dXDivASqr + dYDivBSqr - 1.0;
		if (dF < dEpsilon)
		{
			// F(t0) is close enough to zero, terminate the iteration
			closestX = dXDivA*xRadius;
			closestZ = dYDivB*yRadius;
			iFinal = i;
			break;
		}

		double dFDer = 2.0*(dXDivASqr*dInvTpASqr + dYDivBSqr*dInvTpBSqr);
		double dRatio = dF/dFDer;
		if (dRatio < dEpsilon)
		{
			// t1-t0 is close enough to zero, terminate the iteration
			closestX = dXDivA*xRadius;
			closestZ = dYDivB*yRadius;
			iFinal = i;
			break;
		}

		dT += dRatio;
	}

	if (i == iMax)
	{
		// method failed to converge, let caller know
		iFinal = -1;
		return -FLT_MAX;
	}

	double dDelta0 = closestX - pt.x, dDelta1 = closestZ - pt.y;
	return sqrt(dDelta0*dDelta0 + dDelta1*dDelta1);
}


double Geometry::DistancePointEllipse(Point& pt, double xRadius, double yRadius,
																					const double dEpsilon, const int iMax, int& iFinal, 
																					double& closestX, double& closestZ)
{
	// Source: http://www.geometrictools.com/Documentation/DistancePointToEllipse2.pdf

	// special case of circle
	if (fabs(xRadius-yRadius) < dEpsilon)
	{
		double dLength = sqrt(pt.x*pt.x+pt.y*pt.y);
		return fabs(dLength - xRadius);
	}

	// reflect U = -U if necessary, clamp to zero if necessary
	bool bXReflect;
	if (pt.x > dEpsilon)
	{
		bXReflect = false;
	}
	else if (pt.x < -dEpsilon)
	{
		bXReflect = true;
		pt.x = -pt.x;
	}
	else
	{
		bXReflect = false;
		pt.x = 0.0;
	}

	// reflect V = -V if necessary, clamp to zero if necessary
	bool bYReflect;
	if (pt.y > dEpsilon)
	{
		bYReflect = false;
	}
	else if (pt.y < -dEpsilon)
	{
		bYReflect = true;
		pt.y = -pt.y;
	}
	else
	{
		bYReflect = false;
		pt.y = 0.0;
	}

	// transpose if necessary
	double dSave;
	bool bTranspose;
	if (xRadius >= yRadius)
	{
		bTranspose = false;
	}
	else
	{
		bTranspose = true;
		dSave = xRadius;
		xRadius = yRadius;
		yRadius = dSave;
		dSave = (double)pt.x;
		pt.x = pt.y;
		pt.y = (float)dSave;
	}

	double dDistance;
	if (pt.x != 0.0)
	{
		if (pt.y != 0.0)
		{
			dDistance = Geometry::DistancePointEllipseSpecial(pt, xRadius, yRadius, dEpsilon, iMax,
																																		iFinal, closestX, closestZ);
		}
		else
		{
			double dBSqr = yRadius*yRadius;
			if (pt.x < xRadius - dBSqr/xRadius)
			{
				double dASqr = xRadius*xRadius;
				closestX = dASqr*pt.x/(dASqr-dBSqr);
				double dXDivA = closestX/xRadius;
				closestZ = yRadius*sqrt(fabs(1.0-dXDivA*dXDivA));
				double dXDelta = closestX - pt.x;
				dDistance = sqrt(dXDelta*dXDelta+closestZ*closestZ);
				iFinal = 0;
			}
			else
			{
				dDistance = fabs(pt.x - xRadius);
				closestX = xRadius;
				closestZ = 0.0;
				iFinal = 0;
			}
		}
	}
	else
	{
		dDistance = fabs(pt.y - yRadius);
		closestX = 0.0;
		closestZ = yRadius;
		iFinal = 0;
	}

	if (bTranspose)
	{
		dSave = closestX;
		closestX = closestZ;
		closestZ = dSave;
	}

	if (bYReflect)
	{
		closestZ = -closestZ;
	}

	if (bXReflect)
	{
		closestX = -closestX;
	}

	return dDistance;
}

Point Geometry::EllipseOriginLineIntersect(double xRadius, double yRadius, Point& lineEnd)
{
	double a = xRadius;
	double b = yRadius;
	double denom = sqrt((b*lineEnd.x)*(b*lineEnd.x) + (a*lineEnd.y)*(a*lineEnd.y));
	double x = (a*b*lineEnd.x)/denom;
	double y = (a*b*lineEnd.y)/denom;

	return Point((float)x, (float)y);
}

Point Geometry::GetEllipsePointAtAngle(double xRadius, double yRadius, double angle)
{
	// get a distance that is longer than either radii of the ellipse
	double dist = xRadius + yRadius;

	// find intersection between line from (0,0) to (xx,zz) and the ellipse 
	double xx = cos(angle)*dist;
	double yy = sin(angle)*dist;
  Point point((float)xx, (float)yy);

	return Geometry::EllipseOriginLineIntersect(xRadius, yRadius, point);
}

double Geometry::AngleBisector(double angle1, double angle2)
{
	if(angle1 < 0) 
		angle1 = PI2 + angle1;
	
	if(angle2 < 0) 
		angle2 = PI2 + angle2;
	
	double midAngle;
	if(angle1 > angle2)
	{
		double deltaAngle = angle1 - angle2;
		if(deltaAngle > PI) 
			deltaAngle = deltaAngle - PI2;
		midAngle = angle2 + deltaAngle * 0.5;
	}
	else
	{
		double deltaAngle = angle2 - angle1;
		if(deltaAngle > PI) 
			deltaAngle = deltaAngle - PI2;
		midAngle = angle1 + deltaAngle * 0.5;
	}

	return midAngle;
}

Point Geometry::EllipseNormal(double xRadius, double yRadius, const Point& canonicalPt)
{
	double x = (2*canonicalPt.x) / (xRadius*xRadius);
	double y = (2*canonicalPt.y) / (yRadius*yRadius);
	Point normal((float)x, (float)y);
	normal.Normalize();

	return normal;     
}

int Geometry::SmallestAngleDir(double start, double end)
{
	int dir = 1;
	double dAngle = start - end;
	if(dAngle > 0 && dAngle < PI)
			dir = -1;
	else if(dAngle > 0 && dAngle < -PI)
			dir = -1;

	return dir;
}

double Geometry::AngleBisector(std::vector<double> angles, std::vector<uint>& ccwIndices)
{
	// Set angle bisector so it at the "middle angle" of the set of angles. For 
	// sets with 2 angles this is simple the angle bisector. For set with more
	// than 2 angles, the largest angle between any two adjacent angles is identified.
	// The angle bisector is than set half-way between these two angles such that it 
	// is in the "middle" of the other angles.

	assert(angles.size() > 1);

	if(angles.size() == 2)
	{
		int dir = SmallestAngleDir(angles.at(0), angles.at(1));
		if(dir == 1)
		{
			ccwIndices.push_back(0);
			ccwIndices.push_back(1);
		}
		else
		{
			ccwIndices.push_back(1);
			ccwIndices.push_back(0);
		}

		return AngleBisector(angles.at(0), angles.at(1));
	}
	else
	{
		// find largest angle between any two adjacent angles in the set
		sort(angles.begin(), angles.end());

		double maxAngle = 0;
		uint maxIndex;
		for(uint i = 1; i < angles.size(); ++i)
		{
			double angle = angles.at(i) - angles.at(i-1);
			if(angle > maxAngle)
			{
				maxAngle = angle;
				maxIndex = i;

			}
		}

		// check angle between first and last angle in set
		double angle = angles.at(angles.size()-1) - angles.at(0);
		angle = PI2 - angle;
		if(angle > maxAngle)
		{
			maxAngle = angle;
			maxIndex = 0;
		}
	
		// find bisector of angles with largest angle between them
		double dAngle;
		if(maxIndex > 0)
		{			
			dAngle = angles.at(maxIndex) - angles.at(maxIndex-1);
		}
		else
		{
			dAngle = angles.at(angles.size()-1) - angles.at(0);
			dAngle = PI2 - dAngle;
		}

		double bisector = angles.at(maxIndex) - dAngle * 0.5;
		
		// rotate bisector 180 degrees so it is in the "middle" of the angle set
		bisector += PI;
		if(bisector > PI2)
			bisector -= PI2;

		// create list of angles going in CCW direction between angles used to define the bisector
		for(uint i = maxIndex; i < angles.size(); ++i)
		{
			ccwIndices.push_back(i);
		}

		for(uint i = 0; i < maxIndex; ++i)
		{
			ccwIndices.push_back(i);
		}

		return bisector;
	}

	// the compiler has failed if this point is every reached!
	assert(false);
	return 0;
}

bool Geometry::EllipseLineIntersect(double xRadius, double yRadius, Line& line, std::vector<Point>& intersectPts)
{
	// http://www.codecogs.com/reference/maths/analytical_geometry/the_ellipse.php#sec4

	double slope = (line.end.y - line.start.y) / (line.end.x - line.start.x);
	double yInter = line.start.y - slope*line.start.x;

	double xRadius2 = xRadius*xRadius;
	double yRadius2 = yRadius*yRadius;
	double slope2 = slope*slope;
	double yInter2 = yInter*yInter;

	double a = xRadius2*slope2 + yRadius2;
	double b = 2*xRadius2*slope*yInter;
	double c = xRadius2*(yInter2 - yRadius2);

	double discriminant = b*b - 4*a*c;
	if(discriminant > 0)
	{
		double sqrtRoot = sqrt(discriminant);

		double x = (-b + sqrtRoot) / (2*a);
		double y = slope*x + yInter;
		intersectPts.push_back(Point((float)x, (float)y));

		x = (-b - sqrtRoot) / (2*a);
		y = slope*x + yInter;
		intersectPts.push_back(Point((float)x, (float)y));

		return true;
	}
	else if(discriminant == 0)
	{
		double x = -b / (2*a);
		double y = slope*x + yInter;
		intersectPts.push_back(Point((float)x, (float)y));

		return true;
	}

	return false;
}
