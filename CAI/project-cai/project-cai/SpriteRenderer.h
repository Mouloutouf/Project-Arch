#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

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
		class SpriteRenderer : public Component
		{
		public:

			SpriteRenderer();
			SpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath = nullptr, int _ppu = 1);
			SpriteRenderer(const SpriteRenderer& that, GameObject* _gameObject);
			~SpriteRenderer();

			SpriteRenderer* Clone(GameObject* _gameObject) override;

			void SetActive(bool _value) override;

			void AddToRender();

			Sprite* GetSprite();
			void SetSprite(string _spritePath);

			Vector2f GetSize();
			string GetSpritePath();

			void SetLayer(__Layer _layer);
			__Layer GetLayer();

			void SetOrderInLayer(int _order);
			int GetOrderInLayer();

		protected:

			SpriteObject* spriteObject = nullptr;

			Display* display = nullptr;
		};
	}
}

#endif // !SPRITE_RENDERER_H
