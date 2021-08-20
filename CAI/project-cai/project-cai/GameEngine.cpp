#include "GameEngine.h"

namespace alpha
{
	namespace core
	{
		GameEngine::GameEngine()
		{
			gameWindow = GameWindow("The Arch Project Debug", 1920, 1080);
		}

		GameEngine::~GameEngine()
		{
			for (auto& s : scenes)
				delete s;
		}

		void GameEngine::Init()
		{
			UserInit();

			if (currentScene != nullptr)
			{
				currentScene->Init();
			}
		}

		void GameEngine::UserInit()
		{
			scenes.push_back(new SceneView(&gameWindow, "Game Scene"));

			currentScene = scenes.back();

			AssetView::currentScene = currentScene;
			AssetManager::UserInit();
		}

		void GameEngine::Run(float _elapsedTime)
		{
			gameWindow.window->clear();

			currentScene->Update(_elapsedTime);
			currentScene->Render(gameWindow.window);

			gameWindow.window->display();
		}

		void GameEngine::EventRun(Event& _event, float _elapsedTime)
		{
			currentScene->EventUpdate(_event, _elapsedTime);
		}

		GameWindow* GameEngine::GetGameWindow()
		{
			return &gameWindow;
		}
	}
}
