#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <typeinfo>
#include "Alpha.h"

#include "Component.h"

///\

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

			GameObject* gameObject = nullptr;

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
				Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default });
			GameObject(const GameObject& that);
			GameObject& operator=(const GameObject& that);

			~GameObject();

			/// Methods
			void AddComponent(Component* _component); /* Add Component should be made into a T template method, to retrieve the Component, after creating it. */
			void RemoveComponent(Component* _component);

			template <typename T = Component> T* GetComponent() {
				for (auto& c : components) {
					if (typeid(*c) == typeid(T))
						return dynamic_cast<T*>(c);
				} return nullptr;
			}
			template <typename T = Component> vector<T*> GetComponents() {
				vector<T*> _components;
				for (auto& c : components) {
					if (typeid(*c) == typeid(T))
						_components.push_back(dynamic_cast<T*>(c));
				} return _components;
			}

			vector<Component*>* GetComponentsList();

			int AddChild(GameObject* _gameObject);
			void DeleteChild(int _index);

			GameObject* GetChild(int _index);
			GameObject* GetChild(string _name);
			
			void Init();

			void Start();
			void Update(float _elapsedTime);

			/// Variables
			Transform2D transform;

			GameObject* parent = nullptr;
			vector<GameObject*> children;

			string name;

			Layer layer;
			vector<Tag> tags;

			int index = 0;

		protected:

			int childIndex = -1;

			vector<Component*> components;
		};
	}
}

#endif // !GAME_OBJECT_H
