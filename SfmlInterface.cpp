/*
 * SfmlInterface.cpp
 *
 *  Created on: 27 Sep 2014
 *      Author: Jacques
 */

#include "SfmlInterface.h"

SfmlInterface::SfmlInterface(const float& hres, const float& vres) :
	_hres(hres),
	_vres(vres),
	_window(sf::VideoMode(hres, vres), "Tanks!")
{
	_tankTexture.setSmooth(true);
	_tankTexture.loadFromFile("tank.png", sf::IntRect(0, 0, 50, 50));

	_tank2Texture.setSmooth(true);
	_tank2Texture.loadFromFile("tank2.png", sf::IntRect(0, 0, 50, 50));

	_rocketTexture.setSmooth(true);
	_rocketTexture.loadFromFile("rocket.png", sf::IntRect(0,0, 10,34));

	_explosionTexture01.setSmooth(true);
	_explosionTexture01.loadFromFile("explosion01.png",  sf::IntRect(0, 0, 100,100));

	_crateTexture.setSmooth(true);
	_crateTexture.loadFromFile("crate.png", sf::IntRect(0, 0, 60, 60));

	_mineTexture.setSmooth(true);
	_mineTexture.loadFromFile("mine.png", sf::IntRect(0, 0, 20,20));

	_turretTexture.setSmooth(true);
	_turretTexture.loadFromFile("turret.png", sf::IntRect(0, 0, 50, 50));

	_turretDeadTexture.setSmooth(true);
	_turretDeadTexture.loadFromFile("turret_dead.png", sf::IntRect(0, 0, 50, 50));

	_tankDeadTexture.setSmooth(true);
	_tankDeadTexture.loadFromFile("tank_dead.png", sf::IntRect(0, 0, 50, 50));

	_tank2DeadTexture.setSmooth(true);
	_tank2DeadTexture.loadFromFile("tank2_dead.png", sf::IntRect(0, 0, 50, 50));

	_background.setSmooth(true);
	_background.loadFromFile("grass.png", sf::IntRect(0, 0, 1330, 630));
	_backSprite.setTexture(_background,true);
	_backSprite.setOrigin(665,315);
	_backSprite.setPosition(665,315);
}

SfmlInterface::~SfmlInterface() {}

void SfmlInterface::updateSprites()
{
	_sprites.resize(_gameLogic.numObjects(), Sprite{});

	unsigned int n = 0;
	for (auto tank : _gameLogic._players)
	{
		_sprites[n].setPosition(tank->getCenter().x(), tank->getCenter().y());
		_sprites[n].setRotation(tank->getRotation()*180/PI+90);
		if (n==0)
		{

			if (tank->getHealth() > 0)
			{
				_sprites[n].setOrigin(25,25);
				_sprites[n].setTexture(_tankTexture,true);
			}
			else
			{
				_sprites[n].setOrigin(25,25);
				_sprites[n].setTexture(_tankDeadTexture,true);
			}
		}
		else
		{
			if (tank->getHealth() > 0)
			{
				_sprites[n].setOrigin(25,25);
				_sprites[n].setTexture(_tank2Texture,true);
			}
			else
			{
				_sprites[n].setOrigin(25,25);
				_sprites[n].setTexture(_tank2DeadTexture,true);
			}
		}

		n++;
	}

	for (auto rocket : _gameLogic._rockets)
	{
		_sprites[n].setPosition(rocket->getCenter().x(), rocket->getCenter().y());
		_sprites[n].setRotation(rocket->getRotation()*180/PI+90);
		_sprites[n].setOrigin(5,17);
		_sprites[n].setTexture(_rocketTexture,true);
		n++;
	}

	for (auto crate : _gameLogic._crates)
	{
		_sprites[n].setPosition(crate->getCenter().x(), crate->getCenter().y());
		_sprites[n].setRotation(crate->getRotation()*180/PI+90);
		_sprites[n].setOrigin(20,40);
		_sprites[n].setTexture(_crateTexture,true);
		n++;
	}

	for (auto explosion01 : _gameLogic._explosion01s)
	{
		_sprites[n].setPosition(explosion01->getCenter().x(), explosion01->getCenter().y());
		_sprites[n].setOrigin(20,40);
		_sprites[n].setTexture(_explosionTexture01,true);
		n++;
	}

	for (auto mine : _gameLogic._mines)
	{
		_sprites[n].setPosition(mine->getCenter().x(), mine->getCenter().y());
		_sprites[n].setOrigin(10,10);
		_sprites[n].setRotation(0);
		_sprites[n].setTexture(_mineTexture,true);
		n++;
	}

	for (auto turret : _gameLogic._turrets)
	{
		_sprites[n].setPosition(turret->getCenter().x(), turret->getCenter().y());
		_sprites[n].setOrigin(25,25);
		_sprites[n].setRotation(turret->getRotation()*180/PI+90);
		if (turret->getHealth() <= 0)
			_sprites[n].setTexture(_turretDeadTexture,true);
		else
			_sprites[n].setTexture(_turretTexture,true);

		n++;
	}
}

void SfmlInterface::step(const sf::Time& stepTime)
{
	float time = stepTime.asSeconds();
	_gameLogic.step(time);
}

void SfmlInterface::display()
{
	_window.clear();
	_window.draw(_backSprite);
	for (auto sprite : _sprites)
	{
		_window.draw(sprite);
	}

	_window.display();
}

void SfmlInterface::controllerInput()
{
	//player1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_gameLogic.playControl(FORWARD, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_gameLogic.playControl(REVERSE, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_gameLogic.playControl(ANTI_CLOCKWISE, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_gameLogic.playControl(CLOCKWISE, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			_gameLogic.playControl(FIRE_ROCKET, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			_gameLogic.playControl(PLANT_MINE, 1);

	//player2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_gameLogic.playControl(FORWARD, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_gameLogic.playControl(REVERSE, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_gameLogic.playControl(ANTI_CLOCKWISE, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_gameLogic.playControl(CLOCKWISE, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			_gameLogic.playControl(FIRE_ROCKET, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			_gameLogic.playControl(PLANT_MINE, 2);
}


