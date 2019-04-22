#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb
{
private:
	Sprite  singleBomb;
public:
	// constructor
	Bomb(Texture &bombTexture, Vector2f alienPos)
	{
		singleBomb.setTexture(bombTexture);
		singleBomb.setPosition(alienPos.x + (2 * bombTexture.getSize().x - 30), alienPos.y + 20);
	}

	// check input and set speed
	bool moveDown(float windowSize, float speed)
	{
		bool continueFlight = true; 
		if (singleBomb.getPosition().y < windowSize)
		{
			singleBomb.move(0, speed *  2.0f);
		}
		else
		{
			continueFlight = false;
		}
		return continueFlight;
	}

	// for drawing the bomb
	Sprite getSprite()
	{
		return singleBomb;
	}

	// for collision checking functions
	FloatRect getCollision()
	{
		return singleBomb.getGlobalBounds();
	}
};