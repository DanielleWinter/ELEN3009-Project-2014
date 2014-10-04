/*
 * Boundary.cpp
 *
 *  Created on: 28 Sep 2014
 *      Author: Jacques
 */

#include "Boundary.h"

Boundary::Boundary(const int hres, const int vres, direction side) :
	GameObject(0.1)
{

	float fhres = hres;
	float fvres = vres;

	shared_ptr<Coordinate> c0;
	shared_ptr<Coordinate> c1;
	shared_ptr<Coordinate> c2;
	switch(side)
	{
	case NORTH:
		c0 = make_shared<Coordinate>(Coordinate{-100, 0.01});
		c1 = make_shared<Coordinate>(Coordinate{fhres+100,0});
		c2 = make_shared<Coordinate>(Coordinate{fhres/2,-100});
		break;
	case SOUTH:
		c0 = make_shared<Coordinate>(Coordinate{-100, fvres});
		c1 = make_shared<Coordinate>(Coordinate{fhres-100,fvres+1});
		c2 = make_shared<Coordinate>(Coordinate{fhres-101,fvres+100});
		break;
	case EAST:
		c0 = make_shared<Coordinate>(Coordinate{fhres - 1, -100});
		c1 = make_shared<Coordinate>(Coordinate{fhres+1,fvres+100});
		c2 = make_shared<Coordinate>(Coordinate{fhres+100,fvres/2});
		break;
	case WEST:
		c0 = make_shared<Coordinate>(Coordinate{0.1, -100});
		c1 = make_shared<Coordinate>(Coordinate{0,fvres+100});
		c2 = make_shared<Coordinate>(Coordinate{-300,fvres/2});
		break;
	default:
		//should never happen
		break;
	}

	shared_ptr<Triangle> t0{new Triangle{c0, c1, c2}};
	addTriangle(t0);
	_glued = true;
}

Boundary::~Boundary() {
	// TODO Auto-generated destructor stub
}

