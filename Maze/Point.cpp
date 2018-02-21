#include <iostream>
#include <math.h>
#include "Point.h"

using namespace std;

void Point::Show() const
{
	cout << "(" << x << ", " << y << ")";
}

Point Point::operator +=(Point& p)
{
	x += p.x;
	y += p.y;

	return *this;
}

Point Point::operator +(Point& p)
{
	return Point(x + p.x, y + p.y);
}

Point Point::operator -(Point& p)
{
	return Point(x - p.x, y - p.y);
}

double Point::Length() const
{
	return sqrt(x * x + y * y);
}

Point::ORIENT Point::Classify(Point& p_beg, Point& p_end) const
{
	Point p0 = *this;
	Point a = p_end - p_beg;
	Point b = p0 - p_beg;
	double sa = a.x * b.y - b.x * a.y;

	if (sa > 0.0)
		return LEFT;
	if (sa < 0.0)
		return RIGHT;
	if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0))
		return BEHIND;
	if (a.Length() < b.Length())
		return AHEAD;
	return BETWEEN;
}