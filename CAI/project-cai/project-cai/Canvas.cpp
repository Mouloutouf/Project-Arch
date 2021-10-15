#include "Canvas.h"

namespace alpha
{
	namespace core
	{
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
			width = _width;
			height = _height;
		}
		void UITransform::SetSize(float _right, float _left, float _height)
		{
			if (anchor.stretch.x > 0) {
				right = _right;
				left = _left;
				localPosition.x = (_left / 2) - (_right / 2);
			}
			height = _height;
		}
		void UITransform::SetSize(float _top, float _bottom, float _width, bool second)
		{
			if (anchor.stretch.y > 0) {
				top = _top;
				bottom = _bottom;
				localPosition.y = (_bottom / 2) - (_top / 2);
			}
			width = _width;
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

			return Vector2f((parent->localScale.x / 2) * anchorX, (parent->localScale.y / 2) * anchorY);
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
		Canvas::Canvas(GameObject* _gameObject)
			: Component(_gameObject), transform(dynamic_cast<UITransform*>(_gameObject->transform))
		{
		}
		Canvas::Canvas(GameObject* _gameObject, RenderSpace _renderSpace, Display* _display)
			: Component(_gameObject), transform(dynamic_cast<UITransform*>(_gameObject->transform)), renderSpace(_renderSpace), display(_display)
		{
			if (renderSpace == RenderSpace::ScreenSpace)
				transform->SetSize(display->gameWindow->width, display->gameWindow->height);
		}
		Canvas::Canvas(const Canvas& that, GameObject* _gameObject)
			: Component(that, _gameObject), transform(dynamic_cast<UITransform*>(_gameObject->transform)), renderSpace(that.renderSpace)
		{
		}

		Canvas::~Canvas()
		{
		}

		Canvas* Canvas::Clone(GameObject* _gameObject)
		{
			return new Canvas(*this, _gameObject);
		}
	}
}
