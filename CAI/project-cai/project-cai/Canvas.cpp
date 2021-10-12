#include "Canvas.h"

namespace alpha
{
	namespace core
	{
		UITransform* UITransform::Clone()
		{
			return new UITransform(*this);
		}

		Vector2f UITransform::position()
		{
			Vector2f parentPosition = Vector2f(0, 0);
			if (gameObject->GetParent() != nullptr) parentPosition = gameObject->GetParent()->transform->position();
			Vector2f _pivot = pivot();
			Vector2f _position = localPosition + _pivot;
			return _position + parentPosition;
		}
		float UITransform::rotation() { return 0.0f; }
		Vector2f UITransform::scale()
		{
			Vector2f scale;
			scale.x = anchor.stretch.x > 0 ? parent->localScale.x - right - left : width;
			scale.y = anchor.stretch.y > 0 ? parent->localScale.y - top - bottom : height;
			return scale;
		}

		Canvas::Canvas()
		{
		}

		Canvas::~Canvas()
		{
		}
	}
}
