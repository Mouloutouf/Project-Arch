#include "GameEngine.h"

namespace alpha
{
	namespace core
	{
		GameEngine::GameEngine()
		{
			gameWindow = GameWindow("The Arch Project Debug", 1920, 1080);
		}

		void GameEngine::Init()
		{
			UserInit();

			Assets::currentScene = currentScene;

			if (currentScene != nullptr)
			{
				currentScene->Init();
			}
		}

		void GameEngine::UserInit()
		{
			Scene gameScene = Scene(&gameWindow, "Game Scene");
			scenes.push_back(gameScene);

			currentScene = &scenes.back();

			string extension = ".png";
			vector<string> tileSprites = {"Tile None", "Tile Field Big", "Tile Field Small", "Tile Water", "Tile Woods Big", "Building Storage"};

			for (int i = 0; i < tileSprites.size(); i++)
			{
				GameObject tileGo = GameObject(tileSprites[i]);
				tileGo.AddComponent(new SpriteRenderer(&tileGo, ASSETS_FOLDER + tileSprites[i] + extension, 24));
				Assets::AddAsset(tileGo);
			}
		}

		void GameEngine::Run(float _elapsedTime)
		{
			gameWindow.window->clear();

			currentScene->Update(_elapsedTime);
			currentScene->Render(gameWindow.window);

			gameWindow.window->display();
		}

		void GameEngine::E_Run(Event& _event, float _elapsedTime)
		{
			currentScene->E_Update(_event, _elapsedTime);
		}

		GameWindow* GameEngine::GetGameWindow()
		{
			return &gameWindow;
		}
	}
}
