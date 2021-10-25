#pragma once

#ifndef CANVAS_H
#define CANVAS_H

#include <algorithm>
#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

#include "UITransform.h"
#include "Display.h"

namespace alpha
{
	namespace core
	{
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
