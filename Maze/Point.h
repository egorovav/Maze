#pragma once
#ifndef POINT_H
#define POINT_H
class Point
{
public:

	enum ORIENT
	{
		LEFT,
		RIGHT,
		AHEAD,
		BEHIND,
		BETWEEN
	};

	Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}

	void Show() const;
	ORIENT Classify(Point&, Point&) const;
	double Length() const;

	Point operator +=(Point&);
	Point operator +(Point&);
	Point operator -(Point&);

public:
	double x, y;
};

#endif /* POINT_H */