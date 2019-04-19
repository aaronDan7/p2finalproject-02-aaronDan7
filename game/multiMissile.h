#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
using namespace std;
#include "missile.h"
#include "alienList.h"
#include "multiBomb.h"
#include <SFML/Audio.hpp>
#include "buttons.h"

class multiMissile
{
private:
	list<Missile> missileList;
	int startDelay;
	int kills = 0;
public:
	//constructor, delays missile fire off the start
	multiMissile()
	{
		startDelay = 60;
	}

	void createMissile(Texture &missileTexture, Vector2f shipPos, int waitTime)
	{
		if (startDelay <= 0)
		{
			Missile newMissile(missileTexture, shipPos);
			missileList.push_back(newMissile);
			startDelay = waitTime;
		}
	}

	// move missiles and check collisions for successful shots
	int moveMissiles(RenderWindow &window, alienList &wave)
	{
		button temp;

		if (startDelay > 0) startDelay--;
		list<Missile>::iterator index;
		for (index = missileList.begin(); index != missileList.end();)
		{

			if (!(index->moveUp())) // delete missed shots
			{
				index = missileList.erase(index);
			}
			else if (wave.checkCollision(index->getCollision()))
			{
				// if hit delete missile
				index = missileList.erase(index);

				kills++;
				
			}
			else
			{
				window.draw(index->getSprite());
				index++;
			}
		}
		return kills;
	}
};