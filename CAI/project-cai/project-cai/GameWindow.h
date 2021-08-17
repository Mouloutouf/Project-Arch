#pragma once

#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

namespace alpha
{
	namespace core
	{
		class GameWindow
		{
		public:

			GameWindow(string _projectName = "New Awesome Project", int _width = 1920, int _height = 1080);
			GameWindow(const GameWindow& that);
			GameWindow& operator=(const GameWindow& that);
			~GameWindow();

			RenderWindow* window;

			int width;
			int height;

			string name;
		};
	}
}

#endif // !GAME_WINDOW_H
