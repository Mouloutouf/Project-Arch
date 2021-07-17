#include "Collider.h"

Bounds::Bounds()
{
}
Bounds::Bounds(Vector2f _size)
: size(_size)
{
}

Bounds::~Bounds()
{
}

Collider::Collider()
{
	// Automatic Size Collider if Game Object has a Sprite Renderer
	auto renderer = gameObject->GetComponent<SpriteRenderer>();
	if (renderer != nullptr)
	{
		Vector2f dimensions = renderer->GetSpriteSize();
		bounds = Bounds(dimensions);
	}

	// Otherwise, create a basic bounding box
	bounds = Bounds(Vector2f(1, 1));
}
Collider::Collider(Vector2f _size)
{
	bounds = Bounds(_size);
}
Collider::Collider(Bounds _bounds)
: bounds(_bounds)
{
}

Collider::~Collider()
{
}
