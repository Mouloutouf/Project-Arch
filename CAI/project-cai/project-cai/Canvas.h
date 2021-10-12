#pragma once

#ifndef CANVAS_H
#define CANVAS_H

#include <algorithm>
#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

namespace alpha
{
	namespace core
	{
		enum class AnchorX { Center, Right, Left };
		enum class AnchorY { Center, Top, Bottom };
		enum class AnchorStretch { None, Width, Height, Stretch };

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
			
			void setSize(float _width, float _height)
			{
				width = _width;
				height = _height;
			}
			void setSize(float _right, float _left, float _height) {
				if (anchor.stretch.x > 0) {
					right = _right;
					left = _left;
					localPosition.x = (_left / 2) - (_right / 2);
				}
				height = _height;
			}
			void setSize(float _top, float _bottom, float _width) {
				if (anchor.stretch.y > 0) {
					top = _top;
					bottom = _bottom;
					localPosition.y = (_bottom / 2) - (_top / 2);
				}
				width = _width;
			}
			void setSize(float _top, float _bottom, float _right, float _left) {
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

			Vector2f pivot() {
				float anchorX = (float)anchor.position.x, anchorY = (float)anchor.position.y;
				if (anchor.stretch.x > 0) anchorX = 0;
				if (anchor.stretch.y > 0) anchorY = 0;

				return Vector2f((parent->localScale.x / 2) * anchorX, (parent->localScale.y / 2) * anchorY);
			}

			UITransform* Clone() override;

			Vector2f position() override;
			float rotation() override;
			Vector2f scale() override;

		private:
			Anchor anchor;

			UITransform* parent;

			float x, y;
			float width, height;
			float top, bottom, right, left;
		};

		enum class RenderSpace { ScreenSpace, WorldSpace };

		class Canvas : public Component
		{
		public:

			Canvas();
			~Canvas();

			vector<UITransform*> uiTransforms;

			RenderSpace renderSpace;

		private:

			UITransform* transform;
		};
	}
}

#endif // !CANVAS_H
