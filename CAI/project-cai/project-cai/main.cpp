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

	//RenderWindow* window = new RenderWindow(VideoMode(200, 200), "SFML Works!");

	window->setFramerateLimit(60);

	Clock clock;

	gameEngine.Init();

	while (window->isOpen())
	{
		Time elapsed = clock.restart();
		float elapsedTime = elapsed.asSeconds(); //(float)elapsed.asMicroseconds() / (float)1000000;

		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
			}
			gameEngine.E_Run(event, elapsedTime);
		}

		gameEngine.Run(elapsedTime);
	}

	return 0;
}