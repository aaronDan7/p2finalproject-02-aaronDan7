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
	int spawnDelay;
public:
	multiBomb()
	{
		spawnDelay = 30;
	}

	// if time for a bomb drop, 
	bool bombTimer(int maxTime, int minTime)
	{
		bool over = false; // return value; communicates if wait time is over
		if (spawnDelay <= 0)
		{
			// if wait time up, reset, generate missile
			over = true;
			unsigned seed = time(0);
			srand(seed);
			spawnDelay = (rand() % (maxTime - minTime)) + minTime;
		}
		else
		{
			// decrement wait time
			spawnDelay--;
		}
		return over;
	}

	// create a bomb, add it to the list
	void spawnBomb(Texture &bombTexture, Vector2f alienPos)
	{
		Bomb newBomb(bombTexture, alienPos);
		bombList.push_back(newBomb);
	}

	// handle bomb movement, collison / action, drawing
	// return true if hit player
	// takes in window ref (rendering, window bounds check), shipbounds (collision)
	// speed for downward movement
	bool moveBombs(RenderWindow &win, FloatRect shipBounds, float speed)
	{
		bool hit = false; // if a hit, destroy missile, return true to destroy ship
		list<Bomb>::iterator iter;
		for (iter = bombList.begin(); iter != bombList.end();)
		{

			if (!(iter->moveDown(win.getSize().y, speed))) // if missile can't move up, despawn
			{
				iter = bombList.erase(iter);
			}
			else if (iter->getCollision().intersects(shipBounds)) // alien collision check; check collisions w/ all  aliens
			{
				// collision check action
				iter = bombList.erase(iter);
				hit = true;
			}
			else
			{
				win.draw(iter->getSprite());
				iter++;
			}
		}
		return hit;
	}
};