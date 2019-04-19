#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "alien.h"


class alienList
{
private:
	list<alien> alienWave;
public:
	// create an alien
	void createAlien(Texture &alienTexture, Vector2f alienPos)
	{
		alien newAlien(alienTexture, alienPos);
		alienWave.push_back(newAlien);
	}

	// creat a wave of aliens
	void addAliens(Texture &alienTexture, float num, Vector2u windowBounds)
	{
		Vector2f alienPos(0.0f, 0.0f);
		alienPos.y = windowBounds.y / 50.0f;
		for (float i = 1; i <= num; i++)
		{
			alienPos.x = (windowBounds.x * (i + 1.0f)) / (num + 2.0f) - 50;
			createAlien(alienTexture, alienPos);
		}
	}

	// keeps aliens moving
	bool moveAlienWave(RenderWindow &window, float speed)
	{
		bool keepMoving = true;
		list<alien>::iterator iter = alienWave.begin();
		iter->moveDown(speed);
		if (iter->getYPos() > 590) keepMoving = false;
		window.draw(iter->getSprite());
		iter++;

		while (iter != alienWave.end())
		{
			iter->moveDown(speed);
			window.draw(iter->getSprite());
			iter++;
		}
		return keepMoving;
	}

	// pick randon aliens to drop bombs
	Vector2f setBombPos()
	{
		Vector2f bombPos;
		unsigned seed = time(0);
		srand(seed);
		int alienToDrop = rand() % alienWave.size(); 
		list<alien>::iterator iter;
		iter = alienWave.begin();
		for (int i = 0; i < alienToDrop; i++) iter++;
		bombPos = iter->getPos();
		bombPos.y += 1.0f;
		bombPos.x += 1.0f;
		return bombPos;
	}

	// check aliens for missile collision
	bool checkCollision(FloatRect missileBounds)
	{
		bool hit = false;
		list<alien>::iterator iter;
		iter = alienWave.begin();
		while (iter != alienWave.end() && !hit)
		{
			if (missileBounds.intersects(iter->getCollision()))
			{
				hit = true;
			}
			else iter++;
		}		
		if (hit)
		{
			alienWave.erase(iter);

		}
		return hit;
	}

	// return true if no aliens left
	bool getWin()
	{
		bool win = false;
		if (alienWave.size() < 1)
		{
			win = true;
		}
		return win;
	}
};