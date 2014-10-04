/*
 * GameLogic.h
 *
 */


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include <list>
#include <time.h>
#include <algorithm>
#include "Tank.h"
#include "Rocket.h"
#include "Mine.h"
#include "Crate.h"
#include "ImmovableCrate.h"
#include "Turret.h"
#include "Boundary.h"

class Player_Does_not_Exist{};

enum playerControl
{
	FORWARD,
	REVERSE,
	CLOCKWISE,
	ANTI_CLOCKWISE,
	FIRE_ROCKET,
	PLANT_MINE
};

class GameLogic {
public:
	GameLogic();
	virtual ~GameLogic();
	void loadLevel();
	void loadBoundary(const int hres, const int vres);
	void updateCollisionManager();

	void step(const float time);
	void animate(const float time);
	void clearForces();

	void checkRocketDamage();
	void checkMineDamage();
	void checkTimedDeath();
	void checkHealthDeath();
	void turretAction();
	void playControl(const playerControl&, const int& player);
	int numObjects() const;
	bool isDead(const shared_ptr<GameObject>&);

	list<shared_ptr<Tank>> _players;
	list<shared_ptr<Rocket>> _rockets;
	list<shared_ptr<Crate>> _crates;
	list<shared_ptr<Mine>> _mines;
	list<shared_ptr<Turret>> _turrets;
	//do not add to collision manager:
	list<shared_ptr<GameObject>> _explosion01s;

	shared_ptr<Boundary> _topBound;
	shared_ptr<Boundary> _bottomBound;
	shared_ptr<Boundary> _leftBound;
	shared_ptr<Boundary> _rightBound;

	CollisionManager _collMan{};

	float p1FireTime = clock()/CLOCKS_PER_SEC;
	float p2FireTime = clock()/CLOCKS_PER_SEC;
	float FireTime = 0.25;

	int _hres = 1300;
	int _vres = 700;

private:
	void buildCrate(const Coordinate pos, const bool glued);
	void buildTank(const Coordinate pos);
	void buildTurret(const Coordinate pos);
};

#endif /* GAMELOGIC_H_ */
