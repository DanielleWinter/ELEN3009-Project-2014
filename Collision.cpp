/*
 * Collision.cpp
 *
 *  Created on: 19 Sep 2014
 *      Author: Jacques
 */

#include "Collision.h"



Collision::Collision(const Collision& col) :
	_collider(col._collider),
	_collidee(col._collidee),
	//_approachVelocity(col._approachVelocity),
	_collisionEdge(col._collisionEdge)
{ }

Collision::~Collision() {}

Collision::Collision(
		const shared_ptr<GameObject>& obj1,
		const shared_ptr<GameObject>& obj2)
{
	findCollision(obj1, obj2);
	try
	{
		findCollisionEdge();
	}
	catch(No_Collision&)
	{
		throw No_Collision{};
	}

}

void Collision::findCollision(
		shared_ptr<GameObject> obj1,
		shared_ptr<GameObject> obj2)
{
	if (obj1->hasInside(obj2))
	{
		_collider = obj2;
		_collidee = obj1;
	}
	else if (obj2->hasInside(obj1))
	{
		_collider = obj1;
		_collidee = obj2;
	}
	else
		throw No_Collision{};

}
void Collision::findCollisionEdge()
{
	try
	{
		shared_ptr<Coordinate> penetrator0{
			new Coordinate{_collidee->avgCoordInside(*_collider)}};
		shared_ptr<Coordinate> penetrator1{ new Coordinate{
			(*penetrator0) -
			(_collider->getVelocity())*INF +
			(_collider->getCenter()- _collidee->getCenter())*INF/1000
		}};

		Line penetratingLine{ penetrator0, penetrator1};
		_collisionEdge = _collidee->intersectingLine(penetratingLine);
	}
	catch (No_Line_Intersects&)
	{
		//throw No_Collision{};
	}
}

void Collision::resolve(const float stepTime)
{

	//get normal and check that it points out of the object
	Coordinate normal = _collisionEdge.getNormal();
	if (_collisionEdge.isBelow(make_shared<Coordinate>(_collidee->getCenter())))
	{
		if (normal.y() < 0)
		{
			normal = normal*(-1);
		}
	} else
	{
		if (normal.y() > 0)
		{
			normal = normal*(-1);
		}
	}

	Coordinate colliderVel = _collider->getVelocity();
	Coordinate collideeVel = _collidee->getVelocity();
	float colliderMass = _collider->getMass();
	float collideeMass = _collidee->getMass();
	float totalMass = collideeMass + colliderMass;


	_collider->clearForce();
	_collidee->clearForce();


	Coordinate momentum =
			collideeVel*collideeMass +
			colliderVel*colliderMass;

	Coordinate ColliderImpulse = momentum*-(collideeMass/totalMass)*0.5;
	Coordinate CollideeImpulse = momentum*(colliderMass/totalMass)*0.5;

	auto fwd = normal;

	if(!_collidee->isGlued())
	{
		_collidee->react(CollideeImpulse);
		_collidee->animate(stepTime);
	}
	if (!_collider->isGlued())
	{
		_collider->react(ColliderImpulse);
		_collider->animate(stepTime);
	}
	//solve clipping

	while (_collidee->hasInside(_collider) || _collider->hasInside(_collidee))
	{
		if(!_collider->isGlued())
			_collider->move(normal);
		if(!_collidee->isGlued())
			_collidee->move(normal*(-1));
	}
}

void Collision::printCollisionEdge() const
{
	_collisionEdge.print();
}
