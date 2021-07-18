#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameEngine.h"

int main()
{
	GameEngine gameEngine = GameEngine();

	GameWindow* gameWindow = gameEngine.GetGameWindow();
	RenderWindow* window = gameWindow->window;
	window->setFramerateLimit(60);

	Clock clock;

	gameEngine.Init();

	while (window->isOpen())
	{
		Time elapsed = clock.getElapsedTime();
		clock.restart();
		float elapsedTime = (float)elapsed.asMicroseconds() / (float)1000000;

		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
			}
		}

		gameEngine.Run(elapsedTime);
	}

	return 0;
}