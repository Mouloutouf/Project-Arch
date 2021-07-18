#include "GameObject.h"
#include <typeinfo>

Transform2D::Transform2D()
{
}

Transform2D::~Transform2D()
{
}

GameObject::GameObject(Transform2D _transform, GameObject* _parent, string _name, Layer _layer, Tag _tags[], ...)
: transform(_transform), parent(_parent), name(_name), layer(_layer)
{
	for (int i = 0; i < sizeof(_tags); i++)
	{
		tags.push_back(_tags[i]);
	}

	transform.gameObject = this;

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
T* GameObject::GetComponent()
{
	for (auto &c : components)
	{
		if (typeid(c) == typeid(T))
		{
			return &(T)c;
		}
	}
	return nullptr;
}
template<class T>
T* GameObject::GetComponent(string _name)
{
	if (!_name.empty())
	{
		for (auto &c : components)
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
vector<T*> GameObject::GetComponents()
{
	vector<T*> _components;
	for (auto &c : components)
	{
		if (typeid(c) == typeid(T))
		{
			_components.push_back(&(T)c);
		}
	}
	return _components;
}

vector<Component>* GameObject::GetComponentsList()
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

void GameObject::Update(float _elapsedTime)
{
	for (auto& c : components)
	{
		c.Update(_elapsedTime);
	}
}

void GameObject::Draw(RenderWindow* _window)
{
	for (auto& c : components)
	{
		c.Draw(_window);
	}
}
