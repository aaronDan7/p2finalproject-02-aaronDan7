#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb
{
private:
	Sprite  bombSprite;
public:
	// constructor
	Bomb(Texture &bombTexture, Vector2f alienPos)
	{
		bombSprite.setTexture(bombTexture);
		bombSprite.setPosition(alienPos.x + (2 * bombTexture.getSize().x - 30), alienPos.y + 20);
	}

	// check input and set speed
	bool moveDown(float windH, float speed)
	{
		bool continueFlight = true; 
		if (bombSprite.getPosition().y < windH)
		{
			bombSprite.move(0, speed *  2.0f);
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
		return bombSprite;
	}

	// for collision checking functions
	FloatRect getCollision()
	{
		return bombSprite.getGlobalBounds();
	}

	
};