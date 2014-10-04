/*
 * ImmovableCrate.cpp
 *
 *  Created on: 27 Sep 2014
 *      Author: Jacques
 */

#include "ImmovableCrate.h"

ImmovableCrate::ImmovableCrate() :
	Crate()
{
	_glued = true;
}

ImmovableCrate::~ImmovableCrate() {}

void ImmovableCrate::react(const Coordinate& rhs, const Coordinate& normal)
{
	clearForce();
}
