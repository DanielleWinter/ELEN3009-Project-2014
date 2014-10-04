/*
 * Coordinate.cpp
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#include "Coordinate.h"
Coordinate::Coordinate() :
		_x(0),
		_y(0)
{ }

Coordinate::Coordinate(float x, float y) :
		_x(x),
		_y(y)
{ }

Coordinate::Coordinate(const Coordinate& pos) :
		_x(pos._x),
		_y(pos._y)
{ }

float Coordinate::x() const
{	return this->_x;}

float Coordinate::y() const
{	return _y;}

float Coordinate::angle() const
{	return atan2(_y, _x) + 2*PI;}

float Coordinate::magSquared() const
{	return _x*_x + _y*_y;}

float Coordinate::magnitude() const
{	return sqrt(magSquared());}

void Coordinate::print() const
{
	std::cout << x() << " " << y() << std::endl;
}

void Coordinate::setX(float x)
{	_x = x;}

void Coordinate::setY(float y)
{	_y = y;}

Coordinate Coordinate::operator+(const Coordinate& coord) const
{
	Coordinate coord1{x() + coord.x(), y() + coord.y()};
	return coord1;
}

Coordinate Coordinate::operator-(const Coordinate& coord) const
{
	Coordinate coord1{x() - coord.x(), y() - coord.y()};
	return coord1;
}

void Coordinate::operator+=(const Coordinate& coord)
{
	setX(_x + coord.x());
	setY(_y + coord.y());
}

void Coordinate::operator-=(const Coordinate& coord)
{
	setX(_x - coord.x());
	setY(_y - coord.y());
}

float Coordinate::operator*(const Coordinate& coord) const
{
	float dot = x() * coord.x() + y() * coord.y();
	return dot;
}

bool Coordinate::operator==(const Coordinate& coord) const
{
	if (coord.x() == x() && coord.y() == y())
		return true;
	return false;
}

bool Coordinate::operator>(const Coordinate& coord) const
{
	if (this->magSquared() > coord.magSquared())
		return true;
	else return false;
}

bool Coordinate::operator<(const Coordinate& coord) const
{
	if (this->magSquared() < coord.magSquared())
		return true;
	else return false;
}


Coordinate Coordinate::operator*(const float& rhs) const
{
	float x1 = x()*rhs;
	float y1 = y()*rhs;

	Coordinate tempCoord{x1, y1};
	return tempCoord;
}

Coordinate Coordinate::operator /(const float& rhs) const
{
	float rhs1 = 1/rhs;
	return this->operator *(rhs1);
}

bool Coordinate::operator>(const float& rhs) const
{
	if (this->magSquared() > rhs*rhs)
		return true;
	return false;
}

bool Coordinate::operator<(const float& rhs) const
{
	if (this->magSquared() < rhs*rhs)
		return true;
	return false;
}

bool Coordinate::operator==(const float& rhs) const
{
	if (this->magSquared() == rhs*rhs)
		return true;
	return false;
}

void Coordinate::rotate(const float angle, const Coordinate& center)
{
	this->operator-=(center);
	rotate(angle);
	this->operator +=(center);
}

void Coordinate::rotate(const float angle)
{
	Coordinate col1{(float) cos(angle), (float) sin(angle)};
	Coordinate col2{(float) -sin(angle), (float) cos(angle)};
	float x0 = (*this)*col1;
	float y0 = (*this)*col2;
	setX(x0);
	setY(y0);
}

