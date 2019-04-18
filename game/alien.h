#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class alien
{
private:
	Sprite  singleAlien; 
public:
	// constructor
	alien(Texture &alienTexture, Vector2f alienPos)
	{
		singleAlien.setTexture(alienTexture);
		singleAlien.setPosition(alienPos.x, alienPos.y);
	}

	// move alien towards player
	void moveDown(float speed)
	{
		singleAlien.move(0, speed);
	}

	// send position for bomb creation
	Vector2f getPos()
	{
		return singleAlien.getPosition();
	}

	// return y for check
	float getYPos()
	{
		return singleAlien.getPosition().y;
	}

	FloatRect getCollision()
	{
		return singleAlien.getGlobalBounds();
	}

	// for drawing the alien's sprite
	Sprite getSprite()
	{
		return singleAlien;
	}
};