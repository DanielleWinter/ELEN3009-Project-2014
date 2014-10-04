/*
 * Crate.h
 *
 */

#ifndef CRATE_H_
#define CRATE_H_
#include "CollisionManager.h"
#define CRATEMASS 5

class Crate : public GameObject
{
public:
	Crate();
	virtual ~Crate();
	virtual void react(const Coordinate&);
private:

};

#endif /* TANK_H_ */
