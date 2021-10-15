#pragma once

#ifndef CANVAS_H
#define CANVAS_H

#include <algorithm>
#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

#include "Display.h"

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
			Anchor GetAnchor();

			void SetAnchor(int _posX, int _posY, int _stretchX, int _stretchY);
			
			void SetSize(float _width, float _height);
			void SetSize(float _right, float _left, float _height);
			void SetSize(float _top, float _bottom, float _width, bool second = true);
			void SetSize(float _top, float _bottom, float _right, float _left);

			Vector2f Pivot();

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

			// Canvas uses GameObject in its constructor to set the pointer to the UITransform
			Canvas();
			Canvas(GameObject* _gameObject);
			Canvas(GameObject* _gameObject, RenderSpace _renderSpace, Display* _display);
			Canvas(const Canvas& that, GameObject* _gameObject);
			~Canvas();

			Canvas* Clone(GameObject* _gameObject) override;

			Display* display = nullptr;

			vector<UITransform*> uiTransforms;

			RenderSpace renderSpace = RenderSpace::ScreenSpace;

		private:

			UITransform* transform = nullptr;
		};
	}
}

#endif // !CANVAS_H
