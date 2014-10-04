/*
 * SfmlInterface.h
 *
 *  Created on: 27 Sep 2014
 *      Author: Jacques
 */

#ifndef SFMLINTERFACE_H_
#define SFMLINTERFACE_H_
#include "GameLogic.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;

class SfmlInterface {
public:
	SfmlInterface(const float& hres=1330, const float& vres=630);
	virtual ~SfmlInterface();

	float _hres;
	float _vres;
	sf::RenderWindow _window;
	GameLogic _gameLogic{};

	vector<Sprite> _sprites{};

	Texture _tankTexture;
	Texture _tankDeadTexture;
	Texture _tank2Texture;
	Texture _tank2DeadTexture;
	Texture _rocketTexture;
	Texture _explosionTexture01;
	Texture _crateTexture;
	Texture _mineTexture;
	Texture _turretTexture;
	Texture _turretDeadTexture;

	Texture _background;
	Sprite _backSprite;

	void step(const sf::Time& stepTime);
	void updateSprites();
	void display();

	void controllerInput();
	Clock _clock{};
};

#endif /* SFMLINTERFACE_H_ */
