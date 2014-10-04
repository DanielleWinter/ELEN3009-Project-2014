/*
 * Tank.cpp
 *
 */

#include "Tank.h"

Tank::Tank() :
	GameObject(TANKMASS)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0.0001}};
	shared_ptr<Coordinate> c1{new Coordinate{50.0001,0}};
	shared_ptr<Coordinate> c2{new Coordinate{25.00006,50.0001}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	//tweak these values
	addTriangle(t0);
	setDragCoeff(70);
	_enginePowerFwd = 100000;
	_enginePowerRev = -100000;
	_turningPower = 5;

	_glued = false;
}

Tank::~Tank() {
	// TODO Auto-generated destructor stub
}

void Tank::driveForward()
{
	applyForceLinear(_forward * _enginePowerFwd);
}

void Tank::driveReverse()
{
	applyForceLinear(_forward * _enginePowerRev);
}

void Tank::turnRight()
{
	applyForceAngular(-_turningPower);
}

void Tank::turnLeft()
{
	applyForceAngular(_turningPower);
}

void Tank::react(const Coordinate& rhs)
{
	applyImpulseLinear(rhs); //gives strange behaviour
}

void Tank::fireRocket()
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
	cout << _centerOfMass.x() << " " << _centerOfMass.y() << endl;
}

void Tank::plantMine()
{
	float time = clock();
	time = time/CLOCKS_PER_SEC;
	if (time >= _lastMinePlantTime + _minePlantPeriod)
	{
		if (_minesRemaining > 0)
		{
			_lastMinePlantTime = time;
			_minesRemaining--;
		}
		else
		{
			throw Out_of_Mines{};
		}
	}
	else
	{
		throw Mine_Plant_frequency_too_High{};
	}
}

