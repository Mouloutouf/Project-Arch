#pragma once

#ifndef UI_TRANSFORM_H
#define UI_TRANSFORM_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

namespace alpha
{
	namespace core
	{
		/// Not used as of now
		enum class AnchorX { Center, Right, Left };
		enum class AnchorY { Center, Top, Bottom };
		enum class AnchorStretch { None, Width, Height, Stretch };

		struct Anchor
		{
			Vector2i position = Vector2i(0, 0);
			Vector2i stretch = Vector2i(false, false);
		};

		enum class RenderSpace { ScreenSpace, WorldSpace };

		struct UITransform : Transform2D
		{
			UITransform(GameObject* _parentGameObject);
			UITransform(UITransform* _parent);
			UITransform(UITransform* _parent, RenderSpace _renderMode);
			virtual ~UITransform();

			Anchor GetAnchor();

			void SetAnchor(int _posX, int _posY, int _stretchX, int _stretchY);

			void SetSize(float _width, float _height);
			void SetSize(float _right, float _left, float _height);
			void SetSize(float _top, float _bottom, float _width, bool second);
			void SetSize(float _top, float _bottom, float _right, float _left);

			Vector2f Pivot();

			UITransform* Clone() override;

			Vector2f position() override;
			float rotation() override;
			Vector2f scale() override;

			RenderSpace renderMode;

		private:

			UITransform* parent;

			Anchor anchor;

			Vector2f origin = Vector2f(0, 0);
			float width = 0, height = 0;
			float top = 0, bottom = 0, right = 0, left = 0;
		};
	}
}

#endif // !UI_TRANSFORM_H
