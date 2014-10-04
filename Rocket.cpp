/*
 * Rocket.cpp
 *
 */

#include "Rocket.h"

Rocket::Rocket() :
	GameObject(ROCKETMASS)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0.001}};
	shared_ptr<Coordinate> c1{new Coordinate{5.001,0}};
	shared_ptr<Coordinate> c2{new Coordinate{2.5,20.001}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	//tweak these values
	addTriangle(t0);
	setDragCoeff(100);
	_rocketPower = 250000;
	_lifeTime = 1;
	_health = 100000;
}

Rocket::~Rocket(){ }

void Rocket::clearForce()
{
	_forceLinear = Coordinate{0,0};
	propel();
}

void Rocket::propel()
{
	applyForceLinear(_forward*_rocketPower);
}

void Rocket::react(const Coordinate& bounce)
{
	applyImpulseLinear(bounce*10);
	setDirection(bounce.angle()+PI/2);
}

void Rocket::setDirection(const float angle)
{
	float oldAngle = _forward.angle();
	float dAngle = angle - oldAngle;
	rotate(dAngle);
}
