#include "GameObject.h"

namespace alpha
{
	namespace core
	{
#pragma region Transform

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

#pragma endregion

#pragma region GameObject

		GameObject::GameObject(string _name, Transform2D _transform, GameObject* _parent, Layer _layer, vector<Tag> _tags)
			: transform(_transform), parent(_parent), name(_name), layer(_layer), tags(_tags)
		{
			transform.gameObject = this;

			if (parent != nullptr) {
				childIndex = parent->AddChild(this);
			}
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

			if (parent != nullptr) {
				childIndex = parent->AddChild(this);
			}

			for (auto& ch : that.children) {
				children.push_back(ch);
			}
		}
		GameObject& GameObject::operator=(const GameObject& that)
		{
			if (this != &that)
			{
				transform = that.transform;
				transform.gameObject = this;

				for (auto& c : components)
					delete c;
				components.clear();

				for (int i = 0; i < that.components.size(); ++i)
				{
					components.push_back(that.components[i]->Clone());
					components.back()->gameObject = this;
				}

				parent = that.parent;
				name = that.name;
				layer = that.layer;
				tags = that.tags;

				for (auto& ch : children)
					delete ch;
				children.clear();

				for (int i = 0; i < that.children.size(); i++) {
					children.push_back(that.children[i]);
				}
			}
			return *this;
		}

		GameObject::~GameObject()
		{
			for (auto& ch : children)
				delete ch;

			for (auto& c : components)
				delete c;

			parent->DeleteChild(childIndex);
		}

		vector<Component*>* GameObject::GetComponentsList() { return &components; }

		void GameObject::AddComponent(Component* _component) { components.push_back(_component); }

		void GameObject::RemoveComponent(Component* _component)
		{
			for (int i = 0; i < components.size(); ++i) {
				if (components[i] == _component)
					components.erase(components.begin() + i);
			}
		}

		int GameObject::AddChild(GameObject* _gameObject)
		{
			children.push_back(this);
			return parent->children.size() - 1;
		}

		void GameObject::DeleteChild(int _index)
		{
			if (_index >= 0 && _index < children.size()) {
				delete children[_index];
				children.erase(children.begin() + _index);
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
				for (auto& ch : children) {
					if (_name == ch->name)
						return ch;
				}
			} return nullptr;
		}

		void GameObject::Init()
		{
			for (auto& c : components) {
				c->Init();
			}
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

#pragma endregion
	}
}
