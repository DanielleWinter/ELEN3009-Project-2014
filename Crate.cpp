/*
 * Crate.cpp
 *
 */

#include "Crate.h"

Crate::Crate() :
	GameObject(CRATEMASS)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0}};
	shared_ptr<Coordinate> c1{new Coordinate{51,1}};
	shared_ptr<Coordinate> c2{new Coordinate{50,50}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	shared_ptr<Coordinate> c3{new Coordinate{0,0}};
	shared_ptr<Coordinate> c4{new Coordinate{1,51}};
	shared_ptr<Coordinate> c5{new Coordinate{50,50}};
	shared_ptr<Triangle> t1{new Triangle{c3,c4,c5}};

	//tweak these values
	addTriangle(t0);
	addTriangle(t1);
	setDragCoeff(100);

	_glued = false;
}

Crate::~Crate() {
	// TODO Auto-generated destructor stud
}

void Crate::react(const Coordinate& rhs)
{
	applyImpulseLinear(rhs);
	clearForce();
}

