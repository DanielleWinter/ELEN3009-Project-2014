/*
 * Mine.cpp
 *
 *  Created on: 30 Sep 2014
 *      Author: Jacques
 */

#include "Mine.h"

Mine::Mine() :
GameObject(200)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0.1}};
	shared_ptr<Coordinate> c1{new Coordinate{20,0}};
	shared_ptr<Coordinate> c2{new Coordinate{10,sin(PI/3)/20}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	//tweak these values
	addTriangle(t0);
	setDragCoeff(10);
}

Mine::~Mine() {}

void Mine::react(const Coordinate&)
{
	kill();
}

