/*
 * Mine.h
 *
 *  Created on: 30 Sep 2014
 *      Author: Jacques
 */

#ifndef MINE_H_
#define MINE_H_
#include "CollisionManager.h"

class Mine : public GameObject
{
public:
	Mine();
	virtual ~Mine();
	virtual void react(const Coordinate&);
};

#endif /* MINE_H_ */
