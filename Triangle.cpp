/*
 * Triangle.cpp
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#include "Triangle.h"

Triangle::Triangle(const shared_ptr<Coordinate>& coord0,
		const shared_ptr<Coordinate>& coord1,
		const shared_ptr<Coordinate>& coord2)
{
	_coordinates.push_back(std::shared_ptr<Coordinate>{coord0});
	_coordinates.push_back(std::shared_ptr<Coordinate>{coord1});
	_coordinates.push_back(std::shared_ptr<Coordinate>{coord2});
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

shared_ptr<Coordinate> Triangle::getCoordinate(const int coord) const
{
	if (coord > 2)
		throw argument_exceeds_number_of_coordinates{};

	if (coord < 0)
		throw provide_positive_argument{};

	return _coordinates[coord];
}

bool Triangle::hasInside(const shared_ptr<Coordinate>& coord) const
{
	int len = _coordinates.size();
	for (int i = 0; i != len; i++)
	{
		auto opposingCoord = _coordinates[i];
		Line lin{_coordinates[(i+1)%len], _coordinates[(i+2)%len]};
		if (lin.isBelow(opposingCoord) != lin.isBelow(coord))
		{
			return false;
		}
	}
	return true;
}

vector<shared_ptr<Coordinate>> Triangle::coordsInside(const vector<shared_ptr<Coordinate>>& coords) const
{
	vector<shared_ptr<Coordinate>> coordsInside;

	for(auto coord : coords)
	{
		if(hasInside(coord))
			coordsInside.push_back(coord);
	}
	return coordsInside;
}

vector<shared_ptr<Coordinate>> Triangle::coordsInside(const vector<Triangle> triangles) const
{
	vector<shared_ptr<Coordinate>> coordsInside;

	for (auto tri : triangles)
	{
		auto inside = this->coordsInside(tri._coordinates);
		for(auto coord : inside)
		{
			coordsInside.push_back(coord);
		}
	}
	return coordsInside;
}

void Triangle::rotate(const float angle, const Coordinate& center)
{
	for (auto coord : _coordinates)
	{
		coord->rotate(angle, center);
	}
}

void Triangle::move(const Coordinate change)
{
	for (auto coord : _coordinates)
	{
		(*coord)+=change;
	}
}

Line Triangle::getLine(const int LineNo)
{
	return Line{_coordinates[LineNo%3], _coordinates[(LineNo+1)%3]};
}

bool Triangle::hasInside(const vector<shared_ptr<Coordinate>>& coords) const
{
	for(auto coord : coords)
	{
		if(hasInside(coord))
			return true;
	}
	return false;
}

bool Triangle::hasInside(const vector<Triangle> triangles) const
{
	for (auto tri : triangles)
	{
		if (hasInside(tri._coordinates))
			return true;
	}
	return false;
}
