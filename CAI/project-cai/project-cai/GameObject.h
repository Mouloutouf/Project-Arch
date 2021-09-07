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
		enum class Tag { Default, Main_Camera, Prefab };

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

			GameObject(string _name = "New Game Object", Transform2D _transform = Transform2D(), GameObject* _parent = nullptr,
				Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default });
			GameObject(const GameObject& that);

			~GameObject();

#pragma region Components
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
#pragma endregion

#pragma region Children
			GameObject* CreateChild(GameObject* _gameObject);
			int AddChild(GameObject* _gameObject);
			void RemoveChild(GameObject* _gameObject);

			GameObject* GetChild(int _index);
			GameObject* GetChild(string _name);

			vector<GameObject*>* GetChildren();
#pragma endregion

#pragma region Parent
			void SetParent(GameObject* _gameObject);
			void ExtractFromParent();
			GameObject* GetParent();
#pragma endregion

#pragma region Tags
			vector<Tag>* GetTagsList();
			void AddTag(Tag _tag);
			void RemoveTag(Tag _tag);
			int ContainsTag(Tag _tag);
#pragma endregion

			void Init();

			void Start();
			void Update(float _elapsedTime);
			void EventUpdate(Event& _event, float _elapsedTime);

			Transform2D transform;

			string name;
			Layer layer;
			
			int index = 0;

		private:

			int childIndex = -1;

			GameObject* parent = nullptr;
			vector<GameObject*> children;

			vector<Tag> tags;
			vector<Component*> components;
		};
	}
}

#endif // !GAME_OBJECT_H
