#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Missile
{
private:
	Sprite  missile;
public:
	// constructor take texture and ship position
	Missile(Texture &missileTexture, Vector2f shipPos)
	{
		missile.setTexture(missileTexture);
		missile.setPosition(shipPos.x + (2 * missileTexture.getSize().x), shipPos.y);
	}

	// move missiles and delete missed shots
	bool moveUp()
	{
		bool continueFlight = true; 
		if (missile.getPosition().y > 0)
		{
			missile.move(0, -4.0f);
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
		return missile;
	}

	// when misssile hits alien
	FloatRect getCollision()
	{
		return missile.getGlobalBounds();
	}
};