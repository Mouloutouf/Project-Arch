#pragma once

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Alpha.h"

#include "Utility.h"
#include "GameWindow.h"

#include "SceneView.h"
#include "AssetView.h"

///\

#include "GameObject.h"

namespace alpha
{
	namespace core
	{
		class GameEngine
		{
		public:

			GameEngine();
			~GameEngine();

			void Init();

			void Run(float _elapsedTime);
			void EventRun(Event& _event, float _elapsedTime);

			GameWindow* GetGameWindow();

		protected:

			GameWindow gameWindow;

			SceneView* currentScene;
			vector<SceneView*> scenes;
		};
	}
}

#endif // !GAME_ENGINE_H
