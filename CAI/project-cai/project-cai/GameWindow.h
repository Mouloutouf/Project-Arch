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

	GameWindow(string _projectName = "New Awesome Project", float _width = 1920, float _height = 1080);
	~GameWindow();

	RenderWindow* window;

	Vector2f GetWindowDimensions();

protected:

	void InitializeWindow(float _width, float _height, string _title);

	float width;
	float height;
};

#endif // !GAME_WINDOW_H
