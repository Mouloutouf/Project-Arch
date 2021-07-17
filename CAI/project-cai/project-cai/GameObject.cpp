#include "GameObject.h"
#include <typeinfo>

Transform2D::Transform2D()
{
}
Transform2D::Transform2D(GameObject* _gameObject)
: gameObject(_gameObject)
{
}

Transform2D::~Transform2D()
{
}

GameObject::GameObject()
{
	transform = Transform2D { this };
	transform.scale = Vector2f(1, 1);
}
GameObject::GameObject(Transform2D _transform, GameObject* _parent = nullptr, string _name = "New Game Object", int _layer = 0, int _tags[] = {}, ...)
: transform(_transform), parent(_parent), name(_name), layer(_layer)
{
	for (int i = 0; i < sizeof(_tags); i++)
	{
		tags.push_back(_tags[i]);
	}

	// Initialize Components if any
}

GameObject::~GameObject()
{
	for (auto ch : children)
	{
		delete ch;
	}
}

template<class T>
Component* GameObject::GetComponent()
{
	for (auto c : components)
	{
		if (typeid(c) == typeid(T))
		{
			return &(T)c;
		}
	}
	return nullptr;
}
template<class T>
Component* GameObject::GetComponent(string _name)
{
	if (!_name.empty())
	{
		for (auto c : components)
		{
			if (_name == c.name)
			{
				return &(T)c;
			}
		}
	}
	return nullptr;
}

template<class T>
vector<Component*> GameObject::GetComponents()
{
	vector<Component*> _components;
	for (auto c : components)
	{
		if (typeid(c) == typeid(T))
		{
			_components.push_back(&(T)c);
		}
	}
	return _components;
}

vector<Component>* GameObject::GetAllComponents()
{
	return &components;
}

void GameObject::AddComponent(Component _component)
{
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (&components[i] == _component)
		{
			components.erase(components.begin() + i);
		}
	}
}

GameObject* GameObject::GetChild(int _index)
{
	if (_index > children.size() - 1 || _index < 0) return nullptr;

	return children[_index];
}
GameObject* GameObject::GetChild(string _name)
{
	if (!_name.empty())
	{
		for (auto ch : children)
		{
			if (_name == ch->name)
			{
				return ch;
			}
		}
	}
}
