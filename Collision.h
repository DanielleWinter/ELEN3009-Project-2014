/*
 * Collision.h
 *
 */

#ifndef COLLISION_H_
#define COLLISION_H_
#include "GameObject.h"

class No_Collision : public Collision_Exception {};
class object_Rotated_Into_Collision : public Collision_Exception {};

class Collision {
public:
	Collision(){};
	Collision(const Collision& col);
	Collision(
			const shared_ptr<GameObject>& obj1,
			const shared_ptr<GameObject>& obj2);
	virtual ~Collision();
	void printCollisionEdge() const;
	void resolve(const float stepTime);

	shared_ptr<GameObject> _collider;
	shared_ptr<GameObject> _collidee;

	Line _collisionEdge;

	void findCollisionEdge();
	void findCollision(
			shared_ptr<GameObject> obj1,
			shared_ptr<GameObject> obj2);
};

#endif /* COLLISION_H_ */
