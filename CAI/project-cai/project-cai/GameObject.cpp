#include "GameObject.h"

Transform2D::Transform2D()
{
}

Transform2D::~Transform2D()
{
}

Vector2f Transform2D::position()
{
	Vector2f parentPosition;
	if (gameObject->parent != nullptr) parentPosition = gameObject->parent->transform.position();
	return localPosition + parentPosition;
}

float Transform2D::rotation()
{
	float parentRotation = 0.0f;
	if (gameObject->parent != nullptr) parentRotation = gameObject->parent->transform.rotation();
	return localRotation + parentRotation;
}

Vector2f Transform2D::scale()
{
	Vector2f parentScale;
	if (gameObject->parent != nullptr) parentScale = gameObject->parent->transform.scale();
	return localScale + parentScale;
}

GameObject::GameObject(Transform2D _transform, GameObject* _parent, string _name, Layer _layer, vector<Tag> _tags, ...)
: transform(_transform), parent(_parent), name(_name), layer(_layer), tags(_tags)
{
	transform.gameObject = this;

	// Initialize Components if any
}

GameObject::~GameObject()
{
	for (auto ch : children)
	{
		delete ch;
	}

	for (auto c : components)
	{
		delete c;
	}
}

vector<Component*>* GameObject::GetComponentsList()
{
	return &components;
}

void GameObject::AddComponent(Component* _component)
{
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i] == _component)
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
	return nullptr;
}

void GameObject::Update(float _elapsedTime)
{
	for (auto c : components)
	{
		c->Update(_elapsedTime);
	}
}
