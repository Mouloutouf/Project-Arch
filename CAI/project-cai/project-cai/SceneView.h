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
		extern const string ASSETS_FOLDER;

		class SceneView
		{
		public:

			SceneView();
			SceneView(GameWindow* _gameWindow, string _name = "New Scene");
			~SceneView();

			GameObject* CreateGameObject(string _name = "New Game Object", Transform2D _transform = Transform2D(),
				GameObject* _parent = nullptr, Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default });
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

			void Start();

			void Update(float _elapsedTime);
			void EventUpdate(Event& _event, float _elapsedTime);

			void Render(RenderWindow* _window);

			string name;

			vector<GameObject*> gameObjects;

			/// Utility
			Camera* mainCamera = nullptr;
			Camera* GetMainCamera() {
				GameObject* camObject = FindGameObjectWithTag(Tag::Main_Camera);
				if (camObject)
					return camObject->GetComponent<Camera>();
				return nullptr;
			}
			void CreateSpriteObject(string _name, string _sprite, int _ppu, Vector2f _position);
			///

		private:

			GameWindow* gameWindow = nullptr;

			Display currentDisplay;

			/// DEBUG
			int signSize = 1;
			int signPos = 1;
			///
		};
	}
}

#endif // !SCENE_H
