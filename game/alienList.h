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
	list<alien> alienWave; // hold all the aliens on screen
public:
	// create an alien
	void spawnAlien(Texture &alienTexture, Vector2f alienPos)
	{
		alien newAlien(alienTexture, alienPos);
		alienWave.push_back(newAlien);
	}

	// add a group of aliens usign spawn alien method
	void addAliens(Texture &alienTexture, float num, Vector2u windowBounds)
	{
		Vector2f alienPos(0.0f, 0.0f);
		alienPos.y = windowBounds.y / 50.0f;
		for (float i = 1; i <= num; i++)
		{
			alienPos.x = (windowBounds.x * (i + 1.0f)) / (num + 2.0f) - 50;
			spawnAlien(alienTexture, alienPos);
		}
	}

	// handle missile movement, collison / action, drawing
	// if aliens reach bottom of screen, 
	bool moveAlienWave(RenderWindow &win, float speed)
	{
		bool keepMoving = true; // true until aliens reach the bottom
		list<alien>::iterator iter = alienWave.begin();
		iter->moveDown(speed);
		if (iter->getYPos() > 590) keepMoving = false;
		win.draw(iter->getSprite());
		iter++;

		while (iter != alienWave.end())
		{
			iter->moveDown(speed);
			win.draw(iter->getSprite());
			iter++;
		}
		return keepMoving;
	}

	// get an alien for a bomb position
	Vector2f getBombPos()
	{
		Vector2f bombPos;
		unsigned seed = time(0);
		srand(seed);
		int alienToDrop = rand() % alienWave.size(); // the alien in the order that drops the bomb
		list<alien>::iterator iter;
		iter = alienWave.begin();
		for (int i = 0; i < alienToDrop; i++) iter++;
		bombPos = iter->getPos();
		bombPos.y += 1.0f;
		bombPos.x += 1.0f;
		return bombPos;
	}

	// check all aliens' collisions against individual missile, if hit, destroy alien
	// return true to tell missiles to destroy missile
	bool checkCollision(FloatRect missileBounds)
	{
		bool hit = false; // if hit is true, return to delete in main
		list<alien>::iterator iter;
		iter = alienWave.begin();
		while (iter != alienWave.end() && !hit)
		{
			if (missileBounds.intersects(iter->getCollision())) hit = true;
			else iter++;
		}
		if (hit) iter = alienWave.erase(iter);
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