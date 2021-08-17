#include "GameObject.h"

namespace alpha
{
	namespace core
	{
		Transform2D::Transform2D()
		{
		}
		Transform2D::Transform2D(GameObject* _gameObject, Vector2f _pos, float _rot, Vector2f _scale)
			: gameObject(_gameObject), localPosition(_pos), localRotation(_rot), localScale(_scale)
		{
		}
		Transform2D::Transform2D(const Transform2D& that)
			: gameObject(that.gameObject), localPosition(that.localPosition), localRotation(that.localRotation), localScale(that.localScale)
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

		GameObject::GameObject(string _name, Transform2D _transform, GameObject* _parent, Layer _layer, vector<Tag> _tags, ...)
			: transform(_transform), parent(_parent), name(_name), layer(_layer), tags(_tags)
		{
			transform.gameObject = this;

			// Initialize Components if any
		}
		GameObject::GameObject(const GameObject& that)
			: transform(that.transform), parent(that.parent), name(that.name), layer(that.layer), tags(that.tags)
		{
			transform.gameObject = this;

			for (auto& c : that.components)
			{
				components.push_back(c->Clone());
				components.back()->gameObject = this;
			}
		}
		GameObject& GameObject::operator=(const GameObject& that)
		{
			if (this != &that)
			{
				vector<Component*> newComponents = that.components;

				for (auto& c : components)
					delete c;
				components.clear();

				for (int i = 0; i < newComponents.size(); ++i)
				{
					components.push_back(newComponents[i]->Clone());
					components.back()->gameObject = this;
				}

				transform = that.transform;
				transform.gameObject = this;

				parent = that.parent;
				name = that.name;
				layer = that.layer;
				tags = that.tags;
			}
			return *this;
		}

		GameObject::~GameObject()
		{
			GameObject* deleted = this;

			for (auto& ch : children)
				delete ch;

			for (auto& c : components)
				delete c;
		}

		vector<Component*>* GameObject::GetComponentsList() { return &components; }

		void GameObject::AddComponent(Component* _component) { components.push_back(_component); }

		void GameObject::RemoveComponent(Component* _component)
		{
			for (int i = 0; i < components.size(); ++i)
			{
				if (components[i] == _component)
					components.erase(components.begin() + i);
			}
		}

		GameObject* GameObject::GetChild(int _index)
		{
			if (_index > children.size() - 1 || _index < 0) return nullptr;
			return children[_index];
		}
		GameObject* GameObject::GetChild(string _name)
		{
			if (!_name.empty()) {
				for (auto& ch : children)
				{
					if (_name == ch->name)
						return ch;
				}
			} return nullptr;
		}

		void GameObject::Start()
		{
			for (auto& c : components)
				c->Start();
		}

		void GameObject::Update(float _elapsedTime)
		{
			for (auto& c : components)
				c->Update(_elapsedTime);
		}
	}
}
