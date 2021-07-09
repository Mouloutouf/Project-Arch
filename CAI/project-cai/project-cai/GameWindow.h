#pragma once

#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class GameWindow
{
public:

	GameWindow(string gameName, float width = 1920, float height = 1080);
	~GameWindow();

	RenderWindow * window;

	Vector2f * GetWindowDimensions();

protected:

	void InitializeWindow(float width, float height, string title);

	float windowWidth;
	float windowHeight;
};

#endif // !GAME_WINDOW_H
