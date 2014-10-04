/*
 * Tank.h
 *
 */

#ifndef TANK_H_
#define TANK_H_
#include <time.h>
#include "CollisionManager.h"
#define TANKMASS 10

class Tank : public GameObject
{
public:
	Tank();
	virtual ~Tank();

	void driveForward();
	void driveReverse();
	void turnRight();
	void turnLeft();
	void fireRocket();
	void plantMine();

	virtual void react(const Coordinate&);
private:
	float _enginePowerFwd;
	float _enginePowerRev;
	float _turningPower;

	float _lastRocketFireTime = 0;
	float _rocketFirePeriod = 0.5;

	float _lastMinePlantTime = 0;
	float _minePlantPeriod = 0.5;
	int _minesRemaining = 10;
};

#endif /* TANK_H_ */
