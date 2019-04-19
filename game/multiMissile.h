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
	list<Missile> missileList;
	int spawnDelay;
public:
	//constructor, delays missile fire off the start
	multiMissile()
	{
		spawnDelay = 60;
	}

	void spawnMissile(Texture &missileTexture, Vector2f shipPos, int spawnWaitTime)
	{
		if (spawnDelay <= 0)
		{
			Missile newMissile(missileTexture, shipPos);
			missileList.push_back(newMissile);
			spawnDelay = spawnWaitTime;
		}
	}

	// move missiles and check collisions
	void moveMissiles(RenderWindow &win, alienList &wave)
	{
		if (spawnDelay > 0) spawnDelay--;
		list<Missile>::iterator iter;
		for (iter = missileList.begin(); iter != missileList.end();)
		{

			if (!(iter->moveUp())) // delete missed shots
			{
				iter = missileList.erase(iter);
			}
			else if (wave.checkCollision(iter->getCollision()))
			{
				// if hit delete missile
				iter = missileList.erase(iter);
			}
			else
			{
				win.draw(iter->getSprite());
				iter++;
			}
		}
	}
};