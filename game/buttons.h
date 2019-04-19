#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;


// for start buttons and in game text
class button
{
private:
	RectangleShape start;
	Font font;
public:
	//create text box
	button()
	{
		Vector2f size;
		size.x = 200;
		size.y = 100;
		start.setSize(size);
		start.setPosition(250, 200);
		start.setFillColor(Color::Black);

		if (!font.loadFromFile("C://Windows//Fonts//calibri.ttf"))
		{
			cout << ("couldn't load font");
		}
	}
	
	// display the start button
	void displayStart(RenderWindow & win)
	{
		Text text("start", font, 60);
		text.setPosition(start.getPosition());
		text.setFillColor(Color::White);
		win.draw(start);
		win.draw(text);
	}

	// interact with start
	bool getStart(Vector2f mousepos)
	{
		if (start.getGlobalBounds().contains(mousepos))
		{
			return true;
		}
	}

	// show life counter
	void displayLives(RenderWindow & window, int i)
	{
		string text = "lives remaining:  " + to_string(i-1);
		Text display(text, font, 20);
		display.setPosition(0, 0);
		display.setFillColor(Color::White);
		window.draw(display);
	}

	//shows kill counter
	void displayKills(RenderWindow & window, int i)
	{
		string text = "aliens killed:  " + to_string(i);
		Text display(text, font, 20);
		display.setPosition(0, 570);
		display.setFillColor(Color::White);
		window.draw(display);
	}
};