/*
 * Boundary.h
 *
 *  Created on: 28 Sep 2014
 *      Author: Jacques
 */

#ifndef BOUNDARY_H_
#define BOUNDARY_H_
#include "CollisionManager.h"

enum direction{
	NORTH,
	SOUTH,
	EAST,
	WEST
};


class Boundary : public GameObject
{
public:
	Boundary(const int hres, const int vres, const direction);
	virtual ~Boundary();

	virtual void react(const Coordinate&) {};
};

#endif /* BOUNDARY_H_ */
