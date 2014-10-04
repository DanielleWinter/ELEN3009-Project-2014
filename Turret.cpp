/*
 * Turret.cpp
 *
 *  Created on: 30 Sep 2014
 *      Author: Jacques
 */

#include "Turret.h"


Turret::Turret() :
	GameObject(0)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0.0001}};
	shared_ptr<Coordinate> c1{new Coordinate{50.0001,0}};
	shared_ptr<Coordinate> c2{new Coordinate{25.00006,50.0001}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};
	addTriangle(t0);
	_health = 200;
	_range = 500;
	_glued = true;
}

Turret::~Turret() {
	// TODO Auto-generated destructor stub
}

Coordinate Turret::closestTarget()
{
	Coordinate closest{0,1};
	float distSquaredClosest =_range *90;;
	for (auto target : _targets)
	{
		float distSquared = (target - getCenter()).magSquared();
		if (distSquared < distSquaredClosest )
			closest = Coordinate{target};
	}
	return closest;
}

bool Turret::aim()
{
	Coordinate closest = closestTarget();
	float targetAngle = (closest - getCenter()).angle();
	float turretAngle = _forward.angle();
	float dAngle = targetAngle - turretAngle;
	float dist = (closest - getCenter()).magnitude();

	if (targetAngle > turretAngle)
		applyForceAngular(-_turningPower);
	else
		applyForceAngular(_turningPower);

	if (abs(dAngle) < _accuracy && dist < _range)
		return true;
	else
		return false;
}

void Turret::fireRocket()
{
	float time = clock();
	time = time/CLOCKS_PER_SEC;
	if (time >= _lastRocketFireTime + _rocketFirePeriod)
	{
		_lastRocketFireTime = time;
	}
	else
	{
		throw Rocket_Fire_Frequency_too_High{};
	}
}

void Turret::setTargets(const vector<Coordinate>& targets)
{
	_targets = targets;
}
