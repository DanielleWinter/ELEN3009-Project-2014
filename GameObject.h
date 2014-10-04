/*
 * GameObject.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "Triangle.h"
#include <time.h>
#include <iterator>

class object_is_glued_and_cannot_move{};
class No_Line_Intersects{};
class No_Coordinates_Inside{};

class Rocket_Fire_Frequency_too_High{};
class Mine_Plant_frequency_too_High{};
class Out_of_Mines{};

class GameObject {
public:
	GameObject(float mass);
	virtual ~GameObject(){};

	void kill();
	void damage(const float& dmg);

	Coordinate getCenter();
	Coordinate getVelocity() const;
	Coordinate getForward() const;
	Coordinate getForceLinear() const;
	vector<Triangle> getTriangles() const;
	float getMass() const;
	float getRotation() const;
	float getHealth() const;
	float getTimeOfDeath() const;
	float getBirthTime() const;
	float getLifeTime() const;
	float getForceAngular() const;
	bool isGlued() const;

	void setDragCoeff(const float& dC);
	void setPosition(const Coordinate& pos);
	virtual void clearForce();
	void clearAngularForce();
	void glue();
	void unglue();

	void addTriangle(shared_ptr<Triangle>& tri);

	void move(const Coordinate& change);
	void applyForceLinear(const Coordinate& force);
	void applyForceAngular(const float& force);
	void applyImpulseLinear(const Coordinate& impulse);
	virtual void react(const Coordinate& rhs) {};
	bool animate(const float& time);

	bool hasInside(const shared_ptr<GameObject>& gO);
	bool hasInside(const Coordinate& coord) const;
	Coordinate avgCoordInside(const GameObject& gO);
	Line intersectingLine(const Line& penetratingLine);

protected:
	vector<Triangle> _triangles;

	void rotate(const float& angle);
	bool animateLinear(const float& time);

	float _mass = 1;
	Coordinate _centerOfMass{0, 0};

	Coordinate _forward{0, 1};
	Coordinate _velocityLinear{0, 0};
	Coordinate _forceLinear{0, 0};
	float _dragCoeff = 1;

	float _forceAngular = 0;

	float _health = 100;

	float _birthTime = 0;
	float _timeOfDeath = 0;
	float _lifeTime = 0;

	bool _glued = false;

};

#endif /* GAMEOBJECT_H_ */
