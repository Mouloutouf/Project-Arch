#pragma once

#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

#include "RenderObject.h"
#include "Display.h"

namespace alpha
{
	namespace core
	{
		class TextRenderer : public Component
		{
		public:

			TextRenderer();
			TextRenderer(GameObject* _gameObject, Display* _display, string _string = "", Color _color = Color::White, 
				int _characterSize = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			TextRenderer(const TextRenderer& that, GameObject* _gameObject);
			~TextRenderer();

			TextRenderer* Clone(GameObject* _gameObject) override;

			void SetActive(bool _value) override;

			void AddToRender();

			void SetString(string _string);

			void SetLayer(__Layer _layer);
			__Layer GetLayer();

			void SetOrderInLayer(int _order);
			int GetOrderInLayer();

		protected:

			TextObject* textObject = nullptr;

			Display* display = nullptr;
		};
	}
}

#endif // !TEXT_RENDERER_H
