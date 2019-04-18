#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
using namespace std;
#include "missile.h"
#include "alienList.h"
#include "multiBomb.h"
#include <SFML/Audio.hpp>

class multiMissile
{
private:
	list<Missile> bombList;
	int spawnDelay;
public:
	multiMissile()
	{
		spawnDelay = 0;
	}

	void spawnMissile(Texture &missileTexture, Vector2f shipPos, int spawnWaitTime)
	{
		if (spawnDelay <= 0)
		{
			Missile nMissile(missileTexture, shipPos);
			bombList.push_back(nMissile);
			spawnDelay = spawnWaitTime;
		}
	}

	// move missiles and check collisions
	void moveMissiles(RenderWindow &win, alienList &wave, multiBomb &bombs)
	{
		if (spawnDelay > 0) spawnDelay--;
		list<Missile>::iterator iter;
		for (iter = bombList.begin(); iter != bombList.end();)
		{

			if (!(iter->moveUp())) // delete missed shots
			{
				iter = bombList.erase(iter);
			}
			else if (wave.checkCollision(iter->getCollision())) // missile hit alien
			{
				// collision check action
				iter = bombList.erase(iter);
			}
			else
			{
				win.draw(iter->getSprite());
				iter++;
			}
		}
	}
};