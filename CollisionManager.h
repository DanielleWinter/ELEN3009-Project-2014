/*
 * CollisionManager.h
 *
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
#include "Collision.h"

class CollisionManager {
public:
	CollisionManager(){};
	virtual ~CollisionManager();
	void setGameObjecs(const vector<shared_ptr<GameObject>>& gameObjects);
	void findCollisions();
	void ResolveCollisions(const float stepTime);
	int numCollisions();
	void purgeCollisions();
	void purgeObjects();

private:
	vector<shared_ptr<GameObject>> _gameObjects;
	vector<Collision> _collisions;
};

#endif /* COLLISIONMANAGER_H_ */
