#include "UITransform.h"

namespace alpha
{
	namespace core
	{
		UITransform::UITransform(GameObject* _parentGameObject)
		{
			parent = static_cast<UITransform*>(_parentGameObject->transform);

			if (parent != nullptr)
				renderMode = parent->renderMode;
		}
		UITransform::UITransform(UITransform* _parent)
			: parent(_parent)
		{
			if (_parent != nullptr)
				renderMode = _parent->renderMode;
		}
		UITransform::UITransform(UITransform* _parent, RenderSpace _renderMode)
			: parent(_parent), renderMode(_renderMode)
		{
		}

		UITransform::~UITransform()
		{
		}

		Anchor UITransform::GetAnchor() { return anchor; }

		void UITransform::SetAnchor(int _posX, int _posY, int _stretchX, int _stretchY)
		{
			_posX = clamp(_posX, -1, 1);
			_posY = clamp(_posY, -1, 1);
			anchor.position = Vector2i(_posX, _posY);

			_stretchX = clamp(_stretchX, 0, 1);
			_stretchY = clamp(_stretchY, 0, 1);
			anchor.stretch = Vector2i(_stretchX, _stretchY);
		}

		void UITransform::SetSize(float _width, float _height)
		{
			// Change the localPosition edit to a custom anchor postion for correction
			// Then apply that correction in the position() method
			// And let localPosition only be edited by the user, or when using stretching (which automatically determines the position)

			width = _width;
			origin.x = -(_width / 2) * anchor.position.x;
			height = _height;
			origin.y = -(_height / 2) * anchor.position.y;
		}
		void UITransform::SetSize(float _right, float _left, float _height)
		{
			if (anchor.stretch.x > 0) {
				right = _right;
				left = _left;
				localPosition.x = (_left / 2) - (_right / 2);
			}
			height = _height;
			origin.y = -(_height / 2) * anchor.position.y;
		}
		void UITransform::SetSize(float _top, float _bottom, float _width, bool second)
		{
			if (anchor.stretch.y > 0) {
				top = _top;
				bottom = _bottom;
				localPosition.y = (_bottom / 2) - (_top / 2);
			}
			width = _width;
			origin.x = -(_width / 2) * anchor.position.x;
		}
		void UITransform::SetSize(float _top, float _bottom, float _right, float _left)
		{
			if (anchor.stretch.x > 0 && anchor.stretch.y > 0)
			{
				top = _top;
				bottom = _bottom;
				localPosition.y = (_bottom / 2) - (_top / 2);

				right = _right;
				left = _left;
				localPosition.x = (_left / 2) - (_right / 2);
			}
		}

		Vector2f UITransform::Pivot()
		{
			float anchorX = (float)anchor.position.x, anchorY = (float)anchor.position.y;
			if (anchor.stretch.x > 0) anchorX = 0;
			if (anchor.stretch.y > 0) anchorY = 0;

			float offsetX = parent != nullptr ? parent->scale().x / 2 : 0.0f;
			float offsetY = parent != nullptr ? parent->scale().y / 2 : 0.0f;
			return Vector2f(offsetX * anchorX, offsetY * anchorY);
		}

		UITransform* UITransform::Clone()
		{
			return new UITransform(*this);
		}

		Vector2f UITransform::position()
		{
			Vector2f parentPosition = Vector2f(0, 0);
			if (gameObject->GetParent() != nullptr) parentPosition = gameObject->GetParent()->transform->position();
			Vector2f _pivot = Pivot();
			Vector2f _position = localPosition + _pivot + origin;
			return _position + parentPosition;
		}
		float UITransform::rotation() { return 0.0f; }
		Vector2f UITransform::scale()
		{
			Vector2f scale;
			scale.x = anchor.stretch.x > 0 ? parent->scale().x - right - left : width;
			scale.y = anchor.stretch.y > 0 ? parent->scale().y - top - bottom : height;
			return scale;
		}
	}
}