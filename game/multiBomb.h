#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "bomb.h"
#include "alienList.h"

// 
class multiBomb
{
private:
	list<Bomb> bombList;
	int startDelay;
public:
	// constructer starts alien bombs with wait time
	multiBomb()
	{
		startDelay = 20;
	}

	// create a bomb, add it to the list
	void spawnBomb(Texture &bombTexture, Vector2f alienPos)
	{
		Bomb newBomb(bombTexture, alienPos);
		bombList.push_back(newBomb);
	}

	// moves and checks for hits with player
	bool moveBombs(RenderWindow &window, FloatRect shipBounds, float speed)
	{
		bool hit = false; 
		list<Bomb>::iterator iter;
		for (iter = bombList.begin(); iter != bombList.end();)
		{

			if (!(iter->moveDown(window.getSize().y, speed)))
			{
				iter = bombList.erase(iter);
			}
			else if (iter->getCollision().intersects(shipBounds)) 
			{
				iter = bombList.erase(iter);
				hit = true;
			}
			else
			{
				window.draw(iter->getSprite());
				iter++;
			}
		}
		return hit;
	}

	// randomize bomb drops
	bool bombTimer(int maxTime, int minTime)
	{
		bool over = false; 
		if (startDelay <= 0)
		{
			over = true;
			unsigned seed = time(0);
			srand(seed);
			startDelay = (rand() % (maxTime - minTime)) + minTime;
		}
		else
		{
			startDelay--;
		}
		return over;
	}
};