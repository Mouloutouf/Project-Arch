#include "Collider.h"

Bounds::Bounds()
{
}
Bounds::Bounds(Transform2D* _transform, Vector2f _size, Vector2f _offset)
	: transform(_transform), localSize(_size), localPosition(_offset)
{
}

Bounds::~Bounds()
{
}

Collider::Collider()
{
	// Size the collider automatically if the Game Object has a Sprite Renderer
	auto renderer = gameObject->GetComponent<SpriteRenderer>();
	if (renderer != nullptr)
	{
		Vector2f dimensions = renderer->GetSize();
		bounds = Bounds(&gameObject->transform, dimensions);
	}

	// Otherwise, create a basic bounding box
	bounds = Bounds(&gameObject->transform, Vector2f(1, 1));
}
Collider::Collider(GameObject* _gameObject, Vector2f _size)
	: Component(_gameObject)
{
	bounds = Bounds(&gameObject->transform, _size);
}
Collider::Collider(const Collider& that)
	: Component(that), bounds(that.bounds)
{
}

Collider::~Collider()
{
}

Collider* Collider::Clone()
{
	return new Collider(*this);
}
