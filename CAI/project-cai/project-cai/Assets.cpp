#include "Assets.h"

namespace alpha
{
	namespace core
	{
		void Assets::AddAsset(GameObject& _gameObject)
		{
			prefabs.push_back(_gameObject);
		}
		void Assets::DeleteAsset(string _gameObjectName)
		{
			for (int i = 0; i < prefabs.size(); i++)
			{
				if (prefabs[i].name == _gameObjectName)
					prefabs.erase(prefabs.begin() + i);
			}
		}

		GameObject* Assets::LoadAsset(string _gameObjectName)
		{
			for (auto& g : prefabs)
			{
				if (g.name == _gameObjectName)
					return &g;
			}
			return nullptr;
		}

		GameObject* Assets::InstantiateAsset(GameObject* _gameObject, Vector2f _position, float _rotation, GameObject* _parent)
		{
			for (auto& g : prefabs)
			{
				if (&g == _gameObject) {
					auto go = currentScene->InstantiateGameObject(_gameObject);
					go->transform.localPosition = _position;
					go->transform.localRotation = _rotation;
					go->parent = _parent;

					return go;
				}
			}
			auto _g = GameObject("New Game Object");
			auto _gptr = currentScene->InstantiateGameObject(&_g);
			return _gptr;
		}
	}
}
