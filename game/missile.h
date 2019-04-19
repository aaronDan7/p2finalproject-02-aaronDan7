#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Missile
{
private:
	Sprite  missileSprite;
public:
	// constructor take texture and ship position
	Missile(Texture &missileTexture, Vector2f shipPos)
	{
		missileSprite.setTexture(missileTexture);
		missileSprite.setPosition(shipPos.x + (2 * missileTexture.getSize().x), shipPos.y);
	}

	// move missiles and delete missed shots
	bool moveUp()
	{
		bool continueFlight = true; 
		if (missileSprite.getPosition().y > 0)
		{
			missileSprite.move(0, -4.0f);
		}
		else
		{
			continueFlight = false;
		}
		return continueFlight;
	}
	// for drawing the missile's sprite
	Sprite getSprite()
	{
		return missileSprite;
	}

	// when misssile hits alien
	FloatRect getCollision()
	{
		return missileSprite.getGlobalBounds();
	}
};