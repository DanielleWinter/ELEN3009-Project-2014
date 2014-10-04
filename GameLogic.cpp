/*
 * GameLogic.cpp
 *
 */

#include "GameLogic.h"

GameLogic::GameLogic()
{
	loadLevel();
}

GameLogic::~GameLogic() {}

void GameLogic::step(const float time)
{
	animate(time);
	checkRocketDamage();
	checkMineDamage();
	checkTimedDeath();

	updateCollisionManager();
	_collMan.findCollisions();
	_collMan.ResolveCollisions(time);
	_collMan.purgeCollisions();

	clearForces();

	turretAction();
	checkHealthDeath();
}

void GameLogic::playControl(const playerControl& control, const int& playerNo)
{
	if (playerNo >= _players.size()+1 || playerNo < 1)
		throw Player_Does_not_Exist{};

	auto player = _players.begin();

	for (int n = 1; n < playerNo; ++n) //this is O(n), but it is okay, n stays very small (2 players)
		player = next(player);

	switch (control)
	{
	case FORWARD:
		(*player)->driveForward();
		break;
	case REVERSE:
		(*player)->driveReverse();
		break;
	case CLOCKWISE:
		(*player)->turnRight();
		break;
	case ANTI_CLOCKWISE:
		(*player)->turnLeft();
		break;
	case FIRE_ROCKET:
		if ((*player)->getHealth() > 0)
		{
			try
			{
				(*player)->fireRocket();
				shared_ptr<Rocket> rocket{new Rocket{}};
				Coordinate origin{(*player)->getCenter()};
				origin = origin + (*player)->getForward()*50.0;
				rocket->setPosition(origin);
				rocket->setDirection(-(*player)->getForward().angle() + PI);
				_rockets.push_back(rocket);
			}
			catch (Rocket_Fire_Frequency_too_High&)
			{
				//Do nothing.
				//really though, stop firing rockets for a bit.
			}
		}
		break;
	case PLANT_MINE:
		if ((*player)->getHealth() > 0)
		{
			try
			{
				(*player)->plantMine();
				shared_ptr<Mine> mine{new Mine{}};
				Coordinate origin{(*player)->getCenter()};
				origin = origin + (*player)->getForward()*-50.0;
				mine->setPosition(origin);
				_mines.push_back(mine);
			}
			catch(Mine_Plant_frequency_too_High&)
			{
				//Do Nothing
			}
			catch(Out_of_Mines&)
			{
				//Do nothing
			}
		}
		break;
	default:
		//This should not happen
		break;
	}
}

void GameLogic::updateCollisionManager()
{
	_collMan.purgeCollisions();
	_collMan.purgeObjects();

	vector<shared_ptr<GameObject>> tempGOs;

	tempGOs.push_back(_topBound);
	tempGOs.push_back(_bottomBound);
	tempGOs.push_back(_rightBound);
	tempGOs.push_back(_leftBound);

	for (auto player : _players)
		tempGOs.push_back(player);
    for (auto rocket : _rockets)
    	tempGOs.push_back(rocket);
    for (auto crate : _crates)
        tempGOs.push_back(crate);
    for (auto mine : _mines)
    	tempGOs.push_back(mine);
    for (auto turret : _turrets)
    	tempGOs.push_back(turret);

    _collMan.setGameObjecs(tempGOs);
}

void GameLogic::checkRocketDamage()
{
	for(auto rocket : _rockets)
	{
		for (auto player : _players)
		{
			if (player->hasInside(rocket))
			{
				player->damage(51);
				rocket->kill();
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(player)->getCenter()});
				_explosion01s.push_back(expl01);
				if (player->getHealth() <= 0)
					player->kill();
				return;
			}
		}
		for (auto crate : _crates)
		{
			if (crate->hasInside(rocket))
			{
				crate->damage(10);
				if (crate->getHealth() <= 0)
					crate->kill();
				return;
			}
		}
		for (auto turret : _turrets)
		{
			if (turret->hasInside(rocket))
			{
				rocket->kill();
				turret->damage(51);
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(turret)->getCenter()});
				_explosion01s.push_back(expl01);
				if (turret->getHealth() <= 0)
					turret->kill();
				return;
			}
		}
	}
}

void GameLogic::checkMineDamage()
{
	for (auto mine : _mines)
	{
		for (auto player : _players)
			if (player->hasInside(mine))
			{
				player->damage(51);
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(player)->getCenter()});
				_explosion01s.push_back(expl01);
				if (player->getHealth() <=0)
					player->kill();
				mine->kill();
			}

		for (auto crate : _crates)
			if (crate->hasInside(mine))
			{
				crate->damage(35);
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(crate)->getCenter()});
				_explosion01s.push_back(expl01);
				if (crate->getHealth() <=0)
					crate->kill();
				mine->kill();
			}

		for (auto rocket : _rockets)
			if (rocket->hasInside(mine))
			{
				rocket->kill();
				mine->kill();
			}
	}
}

void GameLogic::checkTimedDeath()
{
	for (auto rocket : _rockets)
	{
		if (rocket->getBirthTime() + rocket->getLifeTime() < clock()/CLOCKS_PER_SEC)
		{
			rocket->kill();
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(Coordinate{(rocket)->getCenter()});
			_explosion01s.push_back(expl01);
		}
	}

	auto n = _explosion01s.begin();
	while (n != _explosion01s.end())
	{
		if ((*n)->getBirthTime() + (*n)->getLifeTime() < clock()/CLOCKS_PER_SEC)
			n = _explosion01s.erase(n);
		else
			++n;
	}
}


void GameLogic::checkHealthDeath()
{
	auto rocket = _rockets.begin();
	while (rocket != _rockets.end())
	{
		if (isDead(*rocket))
		{
			rocket = _rockets.erase(rocket);

		}
		else
			++rocket;
	}

	auto crate = _crates.begin();
	while (crate != _crates.end())
	{
		if (isDead(*crate))
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(Coordinate{(*crate)->getCenter()});
			_explosion01s.push_back(expl01);
			crate = _crates.erase(crate);
		}
		else
			++crate;
	}

	auto mine = _mines.begin();
	while (mine != _mines.end())
	{
		if (isDead(*mine))
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(Coordinate{(*mine)->getCenter()});
			_explosion01s.push_back(expl01);
			mine = _mines.erase(mine);
		}
		else
			++mine;
	}
}

void GameLogic::loadLevel()
{
//	vector<vector<char>> layout{
//		 35  105 175 245 315 385 455 525 595 665 735 805 875 945 1015 1085 1155 1225 1295
//	35	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' ', ' ', ' ', ' '},
//	105	{' ',' ',' ',' ','C',' ',' ',' ',' ','T',' ',' ',' ',' ','C', ' ', ' ', ' ', ' '},
//	175	{' ',' ',' ',' ','C',' ',' ',' ',' ',' ',' ',' ',' ',' ','C', ' ', ' ', ' ', ' '},
//	245	{' ',' ',' ',' ',' ',' ',' ',' ','C','C','C',' ',' ',' ',' ', ' ', ' ', ' ', ' '},
//	315	{' ','P',' ',' ',' ',' ','C',' ',' ',' ',' ',' ','C',' ',' ', ' ', 'C', 'P', ' '},
//	385	{' ',' ',' ',' ',' ',' ',' ',' ','C','C','C',' ',' ',' ',' ', ' ', ' ', ' ', ' '},
//	455	{' ',' ',' ',' ','C',' ',' ',' ',' ',' ',' ',' ',' ',' ','C', ' ', ' ', ' ', ' '},
//	525	{' ',' ',' ',' ','C',' ',' ',' ',' ','T',' ',' ',' ',' ','C', ' ', ' ', ' ', ' '},
//	595	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' ', ' ', ' ', ' '}};

	buildCrate(Coordinate{315, 105}, true);
	buildCrate(Coordinate{1015, 105}, true);
	buildCrate(Coordinate{315, 175}, false);
	buildCrate(Coordinate{1015, 175}, false);
	buildCrate(Coordinate{595, 245}, false);
	buildCrate(Coordinate{665, 245}, true);
	buildCrate(Coordinate{735, 245}, false);
	buildCrate(Coordinate{445, 315}, false);
	buildCrate(Coordinate{875, 315}, false);
	buildCrate(Coordinate{595, 385}, false);
	buildCrate(Coordinate{665, 385}, true);
	buildCrate(Coordinate{735, 385}, false);
	buildCrate(Coordinate{315, 455}, false);
	buildCrate(Coordinate{1015, 455}, false);
	buildCrate(Coordinate{315, 525}, true);
	buildCrate(Coordinate{1015, 525}, true);

	buildTank(Coordinate{105,315});
	buildTank(Coordinate{1225,315});

	buildTurret(Coordinate{665,105});
	buildTurret(Coordinate{665,525});

	loadBoundary(_hres, _vres);
}

void GameLogic::loadBoundary(const int hres, const int vres)
{
	_topBound = shared_ptr<Boundary>{new Boundary{hres, vres, NORTH}};
	_bottomBound = shared_ptr<Boundary>{new Boundary{hres, vres, SOUTH}};
	_leftBound = shared_ptr<Boundary>{new Boundary{hres, vres, WEST}};
	_rightBound = shared_ptr<Boundary>{new Boundary{hres, vres, EAST}};
}

int GameLogic::numObjects() const
{
	int total = 0;
	total += _players.size();
	total += _rockets.size();
	total += _crates.size();
	total += _explosion01s.size();
	total += _mines.size();
	total += _turrets.size();

	return total;
}

void GameLogic::turretAction()
{
	vector<Coordinate> targets;
	for (auto player : _players)
		targets.push_back(player->getCenter());

	for (auto turret : _turrets)
	{
		turret->setTargets(targets);
		if (turret->getHealth() >0)
			if (turret->aim())
			{
				try
				{
					turret->fireRocket();
					shared_ptr<Rocket> rocket{new Rocket{}};
					Coordinate origin{turret->getCenter()};
					origin = origin + turret->getForward()*50.0;
					rocket->setPosition(origin);
					rocket->setDirection(-turret->getForward().angle() + PI);
					_rockets.push_back(rocket);
				}
				catch (Rocket_Fire_Frequency_too_High&)
				{
					//do nothing
				}
			}
	}
}

bool GameLogic::isDead(const shared_ptr<GameObject>& a)
{
	if (a->getHealth() <= 0)
		return true;
	return false;
}

void GameLogic::animate(const float time)
{
	for (auto player : _players)
		player->animate(time);
	for (auto rocket : _rockets)
		rocket->animate(time);
	for (auto crate : _crates)
		crate->animate(time);
	for (auto turret : _turrets)
		turret->animate(time);
}

void GameLogic::clearForces()
{
	for (auto player : _players)
		player->clearForce();
	for (auto rocket : _rockets)
		rocket->clearForce();
	for (auto crate : _crates)
		crate->clearForce();
	for (auto turret : _turrets)
		turret->clearForce();
}

void GameLogic::buildCrate(const Coordinate pos, const bool glued)
{
	shared_ptr<Crate> c1(new Crate{});
	c1->setPosition(pos);
	if (glued)
		c1->glue();
	_crates.push_back(c1);
}

void GameLogic::buildTank(const Coordinate pos)
{
	shared_ptr<Tank> t{new Tank{}};
	t->setPosition(pos);
	_players.push_back(t);
}

void GameLogic::buildTurret(const Coordinate pos)
{
	shared_ptr<Turret> t{new Turret{}};
	t->setPosition(pos);
	_turrets.push_back(t);
}
