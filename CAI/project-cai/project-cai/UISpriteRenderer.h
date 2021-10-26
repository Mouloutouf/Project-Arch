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

			// UI Sprite Renderer uses GameObject in its constructor as it needs to know whether the object is a prefab or not in order to add itself to the render
			UISpriteRenderer();
			UISpriteRenderer(GameObject* _gameObject, Display* _display, __Layer _layer = Layers::DEFAULT_LAYER, string _spritePath = string(), int _ppu = 1);
			UISpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, __Layer _layer = Layers::DEFAULT_LAYER, int _ppu = 1);
			UISpriteRenderer(const UISpriteRenderer& that, GameObject* _gameObject);

			~UISpriteRenderer();

			UISpriteRenderer* Clone(GameObject* _gameObject) override;

			void SetOutline(float _thickness, Color _color);
			bool HasOutline();

			void SetColor(Color _color);

		private:

			UISpriteObject* uiSpriteObject;
		};
	}
}

#endif // !UI_ELEMENT_RENDERER_H
