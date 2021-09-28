#pragma once

#ifndef CANVAS_H
#define CANVAS_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

namespace alpha
{
	namespace core
	{
		struct Anchor
		{
			Vector2i position;
			Vector2i stretch;
		};

		struct UITransform : Transform2D
		{
			Anchor getAnchor() { return anchor; }

			void setAnchor(int _posX, int _posY, int _stretchX, int _stretchY)
			{ 
				_posX = clamp(_posX, -1, 1);
				_posY = clamp(_posY, -1, 1);
				anchor.position = Vector2i(_posX, _posY);

				_stretchX = clamp(_stretchX, 0, 1);
				_stretchY = clamp(_stretchY, 0, 1);
				anchor.stretch = Vector2i(_stretchX, _stretchY);
			}

			void setPosX(float _x) {
				if (anchor.stretch.x > 0) transform->localPosition.x = 0;
				else transform->localPosition.x = origin().x + _x;
			}
			void setPosY(float _y) {
				if (anchor.stretch.y > 0) transform->localPosition.y = 0;
				else transform->localPosition.y = origin().y + _y;
			}

			void setWidth(int _width) {
				if (anchor.stretch.x > 0) width = parent->width - right - left;
				else width = _width;
			}
			void setHeight(int _height) {
				if (anchor.stretch.y > 0) height = parent->height - top - bottom;
				else height = _height;
			}

			void setTop(int _top) {
				if (anchor.stretch.y > 0) {
					top = _top;
					height = parent->height - top - bottom;
					transform->localPosition.y = parent->posY() - (top / 2) + (bottom / 2);
				}
			}
			void setBottom(int _bottom) {
				if (anchor.stretch.y > 0) {
					bottom = _bottom;
					height = parent->height - top - bottom;
					transform->localPosition.y = parent->posY() - (top / 2) + (bottom / 2);
				}
			}
			void setLeft(int _left) {
				if (anchor.stretch.x > 0) {
					left = _left;
					width = parent->width - right - left;
					transform->localPosition.x = parent->posX() - (right / 2) + (left / 2);
				}
			}
			void setRight(int _right) {
				if (anchor.stretch.x > 0) {
					right = _right;
					width = parent->width - right - left;
					transform->localPosition.x = parent->posX() - (right / 2) + (left / 2);
				}
			}

			float top, bottom, right, left;
			float width, height;
			float posX() { return transform->localPosition.x; }
			float posY() { return transform->localPosition.y; }

			Vector2f origin() {
				float anchorX = anchor.position.x, anchorY = anchor.position.y;
				if (anchor.stretch.x > 0) anchorX = 0;
				if (anchor.stretch.y > 0) anchorY = 0;
				return Vector2f((parent->width / 2) * anchorX, (parent->height / 2) * anchorY);
			}

			UITransform* Clone() override;

		private:
			Anchor anchor;

			UITransform* parent;
			Vector2f localSize;

			Transform2D* transform;
		};

		class Canvas : Component
		{
		public:

			Canvas();
			~Canvas();

			vector<UITransform*> uiTransforms;

		private:

			UITransform uiTransform;
		};
	}
}

#endif // !CANVAS_H
