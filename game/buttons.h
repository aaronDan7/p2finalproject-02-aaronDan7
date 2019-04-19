#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;


class button
{
private:
	RectangleShape start;
	RectangleShape lives;
	Font font;
public:
	button()
	{
		Vector2f size;
		size.x = 200;
		size.y = 100;
		start.setSize(size);
		start.setPosition(300, 200);
		start.setFillColor(Color::Black);

		if (!font.loadFromFile("C://Windows//Fonts//calibri.ttf"))
		{
			cout << ("couldn't load font");
		}
	}

	void displayStart(RenderWindow & win)
	{
		Text text("start", font, 50);
		text.setPosition(start.getPosition());
		text.setFillColor(Color::White);
		win.draw(start);
		win.draw(text);
	}

	bool getStart(Vector2f mousepos)
	{
		if (start.getGlobalBounds().contains(mousepos))
		{
			return true;
		}
	}

	void displayLives(RenderWindow & window, int d)
	{
		string text = "lives remaining:  " + to_string(d-1);
		Text display(text, font, 20);
		display.setPosition(0, 0);
		display.setFillColor(Color::White);
		window.draw(display);
	}
};