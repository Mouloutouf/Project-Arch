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
			Vector2f parentPosition = Vector2f(0, 0);
			if (gameObject->GetParent() != nullptr) parentPosition = gameObject->GetParent()->transform->position();
			return localPosition + parentPosition;
		}

		float Transform2D::rotation()
		{
			float parentRotation = 0.0f;
			if (gameObject->GetParent() != nullptr) parentRotation = gameObject->GetParent()->transform->rotation();
			return localRotation + parentRotation;
		}

		Vector2f Transform2D::scale()
		{
			Vector2f parentScale = Vector2f(1, 1);
			if (gameObject->GetParent() != nullptr) parentScale = gameObject->GetParent()->transform->scale();
			return Vector2f(localScale.x * parentScale.x, localScale.y * parentScale.y);
		}

		Transform2D* Transform2D::Clone()
		{
			return new Transform2D(*this);
		}

#pragma endregion

#pragma region GameObject

		GameObject::GameObject(string _name, GameObject* _parent, Transform2D* _transform, Layer _layer, vector<Tag> _tags)
			: transform(_transform), parent(_parent), name(_name), layer(_layer), tags(_tags)
		{
			// Transform
			transform->gameObject = this;

			// Parent
			if (parent != nullptr) {
				parent->AddChild(this);
			}
		}
		GameObject::GameObject(const GameObject& that, GameObject* _parent)
			: parent(that.parent), name(that.name), layer(that.layer), tags(that.tags), active(that.active)
		{
			// Transform
			transform = that.transform->Clone();
			transform->gameObject = this;

			// Parent
			if (_parent != nullptr) {
				parent = _parent;
			}
			if (parent != nullptr) {
				parent->AddChild(this);
			}

			// Children
			for (auto& ch : that.children) {
				new GameObject(*ch, this);
			}

			// Components
			for (auto& c : that.components)
			{
				components.push_back(c->Clone(this));
			}
		}

		GameObject::~GameObject()
		{
			for (auto& c : components)
				delete c;

			if (parent != nullptr)
				parent->RemoveChild(this);

			delete transform;
		}

#pragma region Components
		vector<Component*>* GameObject::GetComponentsList() { return &components; }

		void GameObject::RemoveComponent(Component* _component)
		{
			for (int i = 0; i < components.size(); ++i) {
				if (components[i] == _component) {
					components.erase(components.begin() + i);
					delete components[i];
				}
			}
		}
#pragma endregion

#pragma region Children
		GameObject* GameObject::CreateChild(GameObject* _gameObject)
		{
			children.push_back(_gameObject);
			_gameObject->parent = this;
			_gameObject->childIndex = (int)children.size() - 1;
			return _gameObject;
		}

		void GameObject::AddChild(GameObject* _gameObject)
		{
			children.push_back(_gameObject);
			_gameObject->childIndex = (int)children.size() - 1;
		}
		void GameObject::RemoveChild(GameObject* _gameObject)
		{
			for (int i = 0; i < children.size(); ++i) {
				if (children[i] = _gameObject) {
					children[i]->childIndex = -1;
					children.erase(children.begin() + i);
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
			if (!_name.empty()) {
				for (auto& ch : children) {
					if (_name == ch->name)
						return ch;
				}
			} return nullptr;
		}

		vector<GameObject*>* GameObject::GetChildren() { return &children; }
#pragma endregion

#pragma region Parent
		void GameObject::SetParent(GameObject* _newParent)
		{
			if (_newParent == nullptr) {
				parent = nullptr;
				return;
			}

			if (_newParent != parent)
			{
				if (parent != nullptr)
					parent->RemoveChild(this);
				parent = _newParent;
				parent->AddChild(this);
			}
		}
		void GameObject::ExtractFromParent()
		{
			if (parent != nullptr)
			{
				parent->RemoveChild(this);
				parent = parent->parent;
				if (parent != nullptr)
					parent->AddChild(this);
			}
		}

		GameObject* GameObject::GetParent() { return parent; }
#pragma endregion

#pragma region Tags
		void GameObject::AddTag(Tag _tag)
		{
			if (ContainsTag(_tag) >= 0) return;
			tags.push_back(_tag);
		}
		void GameObject::RemoveTag(Tag _tag)
		{
			int _i = ContainsTag(_tag);
			if (_i >= 0)
				tags.erase(tags.begin() + _i);
		}

		int GameObject::ContainsTag(Tag _tag)
		{
			for (int i = 0; i < tags.size(); ++i) {
				if (tags[i] == _tag)
					return i;
			} return -1;
		}

		vector<Tag>* GameObject::GetTagsList() { return &tags; }
#pragma endregion

		void GameObject::SetActive(bool _value)
		{
			active = _value;
			for (auto& c : components)
				c->SetActive(_value);
		}

		bool GameObject::IsActive()
		{
			return active;
		}

		void GameObject::Init()
		{
			if (!active) return;

			for (auto& c : components) {
				if (c->IsActive()) c->Init();
			}
		}

		void GameObject::Start()
		{
			if (!active) return;

			for (auto& c : components) {
				if (c->IsActive()) c->Start();
			}
		}

		void GameObject::Update(float _elapsedTime)
		{
			if (!active) return;

			for (auto& c : components) {
				if (c->IsActive()) c->Update(_elapsedTime);
			}
		}

		void GameObject::EventUpdate(Event& _event, float _elapsedTime)
		{
			if (!active) return;

			for (auto& c : components) {
				if (c->IsActive()) c->EventUpdate(_event, _elapsedTime);
			}
		}

#pragma endregion
	}
}
