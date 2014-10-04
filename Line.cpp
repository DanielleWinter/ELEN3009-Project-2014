/*
 * Line.cpp
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#include "Line.h"

Line::~Line() {
	// TODO Auto-generated destructor stub
}

Line::Line(const std::shared_ptr<Coordinate>& coord1, const std::shared_ptr<Coordinate>& coord2) :
	_coordinate1(coord1),
	_coordinate2(coord2)
{ }

Line::Line(const Line& lin) : //Note this is important for th report, copy constr copies pointers to coords, resulting in less data moving around.
	_coordinate1(lin._coordinate1),
	_coordinate2(lin._coordinate2)
{ }

bool Line::operator==(const Line& rhs) const
{
	Line lin = rhs;
	Coordinate c11 = *_coordinate1;
	Coordinate c21 = *(lin._coordinate1);

	Coordinate c12 = *_coordinate2;
	Coordinate c22 = *(lin._coordinate2);

	if (c11 == c21 && c12 == c22)
		return true;
	if(c11 == c22 && c12 == c21)
		return true;

	return false;
}

float Line::lengthSquared() const
{
	Coordinate tempCoord = (*_coordinate1) - (*_coordinate2);
	float len = tempCoord.magSquared();
	return len;
}

float Line::length() const
{
	return sqrt(lengthSquared());
}

float Line::getSlope() const
{
	float x1 = _coordinate1->x();
	float y1 = _coordinate1->y();
	float x2 = _coordinate2->x();
	float y2 = _coordinate2->y();

	return ((y1-y2)/(x1-x2));
}

float Line::getYIntercept() const
{
	float x1 = _coordinate1->x();
	float y1 = _coordinate1->y();

	try
	{
		float m = getSlope();
		float c = y1 - (m*x1);
		return c;
	}
	catch(Infinite_Slope&)
	{
		float m = INF;
		float c = y1 - (m*x1);
		return c;
	}


}

float Line::getYVal(float xVal) const
{
	try
	{
		float m = getSlope();
		float c = getYIntercept();
		float y1 = m*xVal + c;
		return y1;
	}
	catch(Infinite_Slope&)
	{
		float m = INF;
		float c = getYIntercept();
		float y1 = m*xVal + c;
		return y1;
	}

}

bool Line::isBelow(const std::shared_ptr<Coordinate>& coord) const
{
	float y0 = coord->y();
	float x0 = coord->x();
	float y1 = getYVal(x0);

	if (y0 < y1)
		return true;
	else
		return false;
}

float Line::isBetween(const float& pt0, const float& bound1, const float& bound2) const
{
	if (pt0 <= bound2 && pt0 >= bound1)
		return true;
	else if ((pt0 >= bound2 && pt0 <= bound1))
		return true;
	return false;
}

Coordinate Line::intersectionPt(const Line& line) const
{

	float x1l1 = _coordinate1->x();
	float x2l1 = _coordinate2->x();
	float y1l1 = _coordinate1->y();
	float y2l1 = _coordinate2->y();

	float x1l2 = line._coordinate1->x();
	float x2l2 = line._coordinate2->x();
	float y1l2 = line._coordinate1->y();
	float y2l2 = line._coordinate2->y();

	float m1 = getSlope();
	float c1 = getYIntercept();

	float m2 = line.getSlope();
	float c2 = line.getYIntercept();

	float x = 0;
	float y = 0;

	if (m1 == m2)
	{
		throw Lines_Do_Not_Intersect{};
	}
	else if (!std::isfinite(m2))
	{
		x = x1l2;
		y = getYVal(x);
	}
	else if (!std::isfinite(m1))
	{
		x = x1l1;
		y = line.getYVal(x);
	}
	else
	{
		x = (c1-c2)/(m2-m1);
		y = getYVal(x);
	}

	if (isBetween(x,x1l1,x2l1) &&
			isBetween(x,x1l2,x2l2) &&
			isBetween(y,y1l1,y2l1) &&
			isBetween(y,y1l2,y2l2))
		return Coordinate{x, y};
	else
		throw Lines_Do_Not_Intersect{};
}

bool Line::intersects(const Line& line) const
{
	try
	{
		intersectionPt(line);
	}
	catch(Lines_Do_Not_Intersect&)
	{
		return false;
	}

	return true;
}

bool Line::isOnLine(const Coordinate& coord) const
{
	float y0 = getYVal(coord.x());
	if (y0 == coord.y())
		return true;
	return false;
}

Coordinate Line::getNormal()
{
	Coordinate normal{};
	Coordinate c2{_coordinate2->x(), _coordinate2->y()};
	Coordinate c1{_coordinate1->x(), _coordinate1->y()};

	c2.rotate(-PI/2, c1);
	if (c1.magSquared() > c2.magSquared())
		normal = c1 - c2;
	else if (c1.magSquared() < c2.magSquared())
		normal = c2 - c1;

	normal = normal/normal.magnitude();
	return normal;
}

void Line::print() const
{
	_coordinate1->print();
	_coordinate2->print();
}
