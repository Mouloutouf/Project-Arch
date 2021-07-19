#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "Component.h"

enum class Tag { Default };

enum class Layer { Default };

struct Transform2D
{
	Transform2D();
	~Transform2D();

	GameObject* gameObject;

	Vector2f position();
	float rotation();
	Vector2f scale();

	Vector2f localPosition;
	float localRotation;
	Vector2f localScale = Vector2f(1, 1);
};

class GameObject
{
public:

	/// Constructors
	GameObject(Transform2D _transform = Transform2D(), GameObject* _parent = nullptr, string _name = "New Game Object", 
		Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default }, 
		...);
	~GameObject();

	/// Methods
	template <typename T> T* GetComponent(); template <typename T> T* GetComponent(string _name);
	template <typename T> vector<T*> GetComponents();

	vector<Component>* GetComponentsList();

	void AddComponent(Component _component);
	void RemoveComponent(Component* _component);

	GameObject* GetChild(int _index); GameObject* GetChild(string _name);

	void Update(float _elapsedTime);
	void Draw(RenderWindow* _window);

	/// Variables
	Transform2D transform;

	GameObject* parent;
	vector<GameObject*> children;

	string name;

	Layer layer;
	vector<Tag> tags;

protected:

	vector<Component> components;
};

#endif // !GAME_OBJECT_H
