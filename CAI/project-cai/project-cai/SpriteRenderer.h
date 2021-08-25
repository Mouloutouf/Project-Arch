#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

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

			void AddToRender();

			Vector2f GetSize();
			Sprite* GetSprite();
			void SetSprite(string _spritePath);

			int pixelsPerUnit = 1;

		protected:

			string spritePath;

			Sprite sprite;
			Texture texture;

			Display* display;
		};
	}
}

#endif // !SPRITE_RENDERER_H
