#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

#include "SpriteRenderer.h"

namespace alpha
{
	namespace core
	{
		struct Bounds
		{
			Bounds();
			Bounds(Transform2D* _transform, Vector2f _size = Vector2f(1, 1), Vector2f _offset = Vector2f(0, 0));
			~Bounds();

			Vector2f localSize; // e.g. base or initial size, with no scale applied
			Vector2f size() { return Vector2f(localSize.x * transform->scale().x, localSize.y * transform->scale().y); }

			Vector2f extents() { return localSize / 2.0f; }

			Vector2f localPosition; // e.g. offset
			Vector2f center() { return transform->position() + localPosition; }

			Vector2f min() { return Vector2f(center().x - extents().x, center().y - extents().y); }
			Vector2f max() { return Vector2f(center().x + extents().x, center().y + extents().y); }

			Transform2D* transform;
		};

		class Collider : public Component
		{
		public:

			Collider();
			Collider(Vector2f _size);
			Collider(const Collider& that, GameObject* _gameObject);
			~Collider();

			Collider* Clone(GameObject* _gameObject) override;

			Bounds bounds;
		};
	}
}

#endif // !COLLIDER_H
