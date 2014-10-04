/*
 * Turret.h
 *
 *  Created on: 30 Sep 2014
 *      Author: Jacques
 */

#ifndef TURRET_H_
#define TURRET_H_
#include "CollisionManager.h"
using namespace std;

class Turret : public GameObject {
public:
	Turret();
	virtual ~Turret();

	virtual void react(const Coordinate& thing){};
	bool aim();
	void fireRocket();
	void setTargets(const vector<Coordinate>& targets);
private:
	Coordinate closestTarget();

	vector<Coordinate> _targets{};

	float _turningPower = 5;
	float _lastRocketFireTime = 0;
	float _rocketFirePeriod = 0.5;

	float _range = 500;
	float _accuracy = PI/5;

};

#endif /* TURRET_H_ */
