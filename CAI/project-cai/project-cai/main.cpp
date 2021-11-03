#include "Alpha.h"

#include "GameEngine.h"

using namespace alpha;
using namespace core;

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
		Time elapsed = clock.restart();
		float elapsedTime = elapsed.asSeconds();

		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
			if (event.type == Event::KeyPressed) {
				if (event.key.alt == Keyboard::F4)
					window->close();
			}

			gameEngine.EventRun(event, elapsedTime);
		}

		gameEngine.Run(elapsedTime);
	}

	return 0;
}