#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Alpha.h"
#include "Core.h"
#include "Game.h"

///\

#include "GameWindow.h"
#include "Display.h"

namespace alpha
{
	using namespace game;

	namespace core
	{
		class SceneView
		{
		public:

			SceneView();
			SceneView(GameWindow* _gameWindow, string _name = "New Scene");
			~SceneView();

			GameObject* CreateGameObject(string _name = "New Game Object", GameObject* _parent = nullptr, Transform2D _transform = Transform2D(),
				 Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default });
			GameObject* InstantiateGameObject(GameObject* _gameObject);
			void DestroyGameObject(GameObject* _gameObject);

			GameObject* FindGameObjectWithName(string _name);
			GameObject* FindGameObjectWithTag(Tag _tag);

			template <typename T = Component> vector<T*> FindAllComponentsOfType() {
				vector<T*> cList;
				for (auto& go : gameObjects) {
					T* _c = go->GetComponent<T>();
					if (_c != nullptr)
						cList.push_back(_c);
				} return cList;
			}

			void Init();
			void UserInit();

			void Play();
			bool inPlay;

			void Update(float _elapsedTime);
			void EventUpdate(Event& _event, float _elapsedTime);

			void Render();

			/// Utility
			/// TO-DO :
			/// Find a better way to cache the Main Camera
			Camera* mainCamera = nullptr;
			Camera* GetMainCamera() {
				GameObject* camObject = FindGameObjectWithTag(Tag::Main_Camera);
				if (camObject)
					return camObject->GetComponent<Camera>();
				return nullptr;
			}
			GameObject* CreateSpriteObject(string _name, string _sprite, int _ppu, Vector2f _position);
			Display* GetCurrentDisplay() { return &currentDisplay; }
			///

			string name;

		private:

			vector<GameObject*> gameObjects;

			Display currentDisplay;

			GameWindow* gameWindow = nullptr;
		};
	}
}

#endif // !SCENE_H
