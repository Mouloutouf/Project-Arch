#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameEngine.h"

int main()
{
	GameEngine * gameEngine = new GameEngine();

	GameWindow * gameWindow = gameEngine->GetWindow();
	RenderWindow * window = gameWindow->window;
	window->setFramerateLimit(60);

	Clock myClock;

	gameEngine->Start();

	while (window->isOpen())
	{
		Time elapsed = myClock.getElapsedTime();
		myClock.restart();
		float elapsedTime = (float)elapsed.asMicroseconds() / (float)1000000;

		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
			}
		}

		gameEngine->Run(elapsedTime);
	}

	return 0;
}