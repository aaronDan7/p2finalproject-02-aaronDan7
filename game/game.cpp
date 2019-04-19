//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 
#include "multiMissile.h"
#include "multiBomb.h"
#include "buttons.h"

//============================================================
// Aaron Hill
// 4/6/19
// program 7 space invaders
//============================================================

void moveShip(Sprite& ship)
{
	const float DISTANCE = 5.0;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		// left arrow is pressed: move our ship left 5 pixels
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		ship.move(-DISTANCE, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		// right arrow is pressed: move our ship right 5 pixels
		ship.move(DISTANCE, 0);
	}
}


int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "invaders from space");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	Music music;
	if (!music.openFromFile("song.ogg"))
	{
		cout << "Unable to load music!" << endl;
		exit(EXIT_FAILURE);
	}

	music.play();

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	Texture shipTexture;
	if (!shipTexture.loadFromFile("ship.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture alienTexture;
	if (!alienTexture.loadFromFile("alien.jpg"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture bombTexture;
	if (!bombTexture.loadFromFile("bomb.png"))
	{
		cout << "Unable to load bomb texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture missileTexture;
	if (!missileTexture.loadFromFile("missile.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Sprite background;
	background.setTexture(starsTexture);
	//background.setScale(1.5, 1.5);

	Sprite ship;
	ship.setTexture(shipTexture);
	Sprite ship2;
	ship.setTexture(shipTexture);
	Sprite ship3;
	ship.setTexture(shipTexture);

	Sprite win;
	Texture winTexture;
	if (!winTexture.loadFromFile("win.png"))
	{
		cout << "Unable to load winner texture!" << endl;
		exit(EXIT_FAILURE);
	}
	win.setTexture(winTexture);

	Sprite lose;
	Texture loseTexture;
	if (!loseTexture.loadFromFile("lose.png"))
	{
		cout << "Unable to load loser texture!" << endl;
		exit(EXIT_FAILURE);
	}
	lose.setTexture(loseTexture);


	multiMissile missiles;
	alienList waveOne;
	alienList waveTwo;
	multiBomb bombs;

	float shipX = window.getSize().x / 2.0f;
	float shipY = 550;

	ship.setPosition(shipX, shipY);

	waveOne.addAliens(alienTexture, 10, window.getSize());
	waveTwo.addAliens(alienTexture, 10, window.getSize());

	int deathCount = 3;
	button livesRemain;
	string gameControl = "paused";

	button txtDisplay;
	bool start = false;
	while (window.isOpen())
	{

		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;

		if (!start)
		{

			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonReleased)
				{
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					start = txtDisplay.getStart(mousePos);
					gameControl = "playing";
				}
			}
			
			window.clear();
			txtDisplay.displayStart(window);
			window.display();
		}

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && gameControl == "playing")
			{
				if (event.key.code == Keyboard::Space)
				{
					missiles.spawnMissile(missileTexture, ship.getPosition(), 2);
				}
			}
		}

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);
		txtDisplay.displayLives(window, deathCount);

		// manage gamemode
		if (gameControl == "playing")
		{
			moveShip(ship);
			window.draw(ship);

			if (!(waveOne.moveAlienWave(window, 0.3)))
			{
				gameControl = "lose";
			}
			
			if (bombs.bombTimer(300, 50)) // hard code bomb timing
			{
				bombs.spawnBomb(bombTexture, waveOne.getBombPos());
			}

			// check deaths / set bomb speed
			if (bombs.moveBombs(window, ship.getGlobalBounds(), 0.6))
			{
				if (deathCount > 2)
				{
					deathCount--;
					window.draw(ship2);
				}
				else if (deathCount > 1)
				{
					deathCount--;
					window.draw(ship3);
				}
				else
				gameControl = "lose";
			}
			missiles.moveMissiles(window, waveOne, bombs);
			

			if ((gameControl == "playing") && (waveOne.getWin()))
			{
				
				gameControl = "round2"; // change levels
			}
		} 
		
		// repeat code for level 2
		if (gameControl == "round2")
		{
			moveShip(ship);
			window.draw(ship);

			if (!(waveTwo.moveAlienWave(window, 0.3)))
			{
				gameControl = "lose";
			}
			 
			if (bombs.bombTimer(100, 20)) // hard code bomb timing
			{
				bombs.spawnBomb(bombTexture, waveTwo.getBombPos()); 
			}
			if (bombs.moveBombs(window, ship.getGlobalBounds(), 0.7))
			{
				if (deathCount > 2)
				{
					deathCount--;
					window.draw(ship2);
				}
				else if (deathCount > 1)
				{
					deathCount--;
					window.draw(ship3);
				}
				else
					gameControl = "lose";
			}
			
			missiles.moveMissiles(window, waveTwo, bombs);

			if ((gameControl == "playing") && (waveTwo.getWin()))
			{
				gameControl = "win"; // end game
			}
		}
		
		if (gameControl == "win")
		{
			window.draw(win);

		}
		if (gameControl == "lose")
		{
			window.draw(lose);
		}

		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

	} // end body of animation loop

	return 0;
}


