/*
 * SfmlGameSprite.h
 *
 */

#ifndef SFMLGAMESPRITE_H_
#define SFMLGAMESPRITE_H_
#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Rocket.h"
#include "Crate.h"
#include "ImmovableCrate.h"

class SfmlGameSprite : public sf::Sprite
{
public:
	SfmlGameSprite();
	virtual ~SfmlGameSprite();
	virtual void Update() = 0;
	virtual void changePosition(const float x, const float y) = 0;
	virtual void animate(const float time) = 0; //remove this

	shared_ptr<GameObject>_object;
};

#endif /* SFMLGAMESPRITE_H_ */
