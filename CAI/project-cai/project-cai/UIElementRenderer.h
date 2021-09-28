#pragma once

#ifndef UI_ELEMENT_RENDERER_H
#define UI_ELEMENT_RENDERER_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

#include "RenderObject.h"
#include "Display.h"

#include "SpriteRenderer.h"

namespace alpha
{
	namespace core
	{
		class UISpriteRenderer : public SpriteRenderer
		{
		public:

			UISpriteRenderer();
			UISpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath = nullptr, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			UISpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			UISpriteRenderer(const UISpriteRenderer& that, GameObject* _gameObject);

			~UISpriteRenderer();

			UISpriteRenderer* Clone(GameObject* _gameObject) override;

			void CreateRenderObject(string _spritePath, int _ppu, __Layer _layer) override;
			void CreateRenderObject(Texture _texture, int _ppu, __Layer _layer) override;
		};
	}
}

#endif // !UI_ELEMENT_RENDERER_H
