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
		list<Bomb>::iterator index;
		for (index = bombList.begin(); index != bombList.end();)
		{

			if (!(index->moveDown(window.getSize().y, speed)))
			{
				index = bombList.erase(index);
			}
			else if (index->getCollision().intersects(shipBounds)) 
			{
				index = bombList.erase(index);
				hit = true;
			}
			else
			{
				window.draw(index->getSprite());
				index++;
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