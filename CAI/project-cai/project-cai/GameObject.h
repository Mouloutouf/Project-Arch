#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <typeinfo>

using namespace std;
using namespace sf;

#include "Component.h"

namespace alpha
{
	namespace core
	{
		enum class Tag { Default, Main_Camera };

		enum class Layer { Default };

		struct Transform2D
		{
			Transform2D();
			Transform2D(GameObject* _gameObject, Vector2f _pos = Vector2f(0, 0), float _rot = 0.0f, Vector2f _scale = Vector2f(1, 1));
			Transform2D(const Transform2D& that);
			~Transform2D();

			GameObject* gameObject;

			Vector2f position();
			float rotation();
			Vector2f scale();

			Vector2f localPosition = Vector2f(0, 0);
			float localRotation = 0.0f;
			Vector2f localScale = Vector2f(1, 1);
		};

		class GameObject
		{
		public:

			/// Constructors
			GameObject(string _name = "New Game Object", Transform2D _transform = Transform2D(), GameObject* _parent = nullptr,
				Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default },
				...);
			GameObject(const GameObject& that);
			template <typename T = Component> void CopyComponent(T* _component)
			{
				components.push_back(new T(*_component));
				components.back()->gameObject = this;
			}
			GameObject& operator=(const GameObject& that);
			~GameObject();

			/// Methods
			template <typename T = Component> T* GetComponent()
			{
				for (auto& c : components)
				{
					T* def = nullptr;
					if (typeid(*c) == typeid(T))
						return dynamic_cast<T*>(c);
				}
				return nullptr;
			}
			template <typename T = Component> vector<T*> GetComponents()
			{
				vector<T*> _components;
				for (auto& c : components)
				{
					if (typeid(*c) == typeid(T))
						_components.push_back(dynamic_cast<T*>(c));
				}
				return _components;
			}

			vector<Component*>* GetComponentsList();

			void AddComponent(Component* _component);
			void RemoveComponent(Component* _component);

			GameObject* GetChild(int _index); GameObject* GetChild(string _name);

			void Start();
			void Update(float _elapsedTime);

			/// Variables
			Transform2D transform;

			GameObject* parent = nullptr;
			vector<GameObject*> children;

			string name;

			Layer layer;
			vector<Tag> tags;

		protected:

			vector<Component*> components;
		};
	}
}

#endif // !GAME_OBJECT_H
