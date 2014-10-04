/*
 * CollisionManager.cpp
 *
 */

#include "CollisionManager.h"

CollisionManager::~CollisionManager() { }

void CollisionManager::setGameObjecs(const vector<shared_ptr<GameObject>>& gameObjects)
{
	_gameObjects = gameObjects;
}

void CollisionManager::findCollisions()
{
	for (unsigned go1 = 0; go1 < _gameObjects.size()-1; go1++)
	{
		for (unsigned go2 = go1+1; go2 < _gameObjects.size(); go2++)
		{
			if ( _gameObjects[go1]->hasInside(_gameObjects[go2]) ||
				(_gameObjects[go2]->hasInside(_gameObjects[go1])))
			{
				try
				{
					Collision col{_gameObjects[go1], _gameObjects[go2]};
					_collisions.push_back(col);
				}
				catch(No_Collision&)
				{
					//Do Nothing
				}
				catch(object_Rotated_Into_Collision&)
				{
					//Do Nothing
				}
			}
		}
	}
}

void CollisionManager::ResolveCollisions(const float stepTime)
{
	for (auto col : _collisions)
	{
		col.resolve(stepTime);
	}
}

int CollisionManager::numCollisions()
{
	return _collisions.size();
}

void CollisionManager::purgeCollisions()
{
	_collisions.clear();
}

void CollisionManager::purgeObjects()
{
	_gameObjects.clear();
}

