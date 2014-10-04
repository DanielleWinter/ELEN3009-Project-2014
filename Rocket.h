/*
 * Rocket.h
 *
 */

#ifndef ROCKET_H_
#define ROCKET_H_
#include "CollisionManager.h"
#define ROCKETMASS 2

class Rocket : public GameObject
{
public:
	Rocket();
	virtual ~Rocket();
	void propel();
	virtual void react(const Coordinate&);
	void setDirection(const float angle);

//private:
	virtual void clearForce();
	float _rocketPower;
};

#endif /* ROCKET_H_ */
