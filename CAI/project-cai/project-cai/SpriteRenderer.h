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
			SpriteRenderer(GameObject* _gameObject, Display* _display);
			SpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			SpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			SpriteRenderer(const SpriteRenderer& that, GameObject* _gameObject);

			~SpriteRenderer();

			SpriteRenderer* Clone(GameObject* _gameObject) override;

			virtual void CreateRenderObject(string _spritePath, int _ppu, __Layer _layer);
			virtual void CreateRenderObject(Texture _texture, int _ppu, __Layer _layer);
			template <typename T = SpriteObject> void CreateRenderObject(T* _spriteObject)
			{
				spriteObject = new T(*_spriteObject);
				AddToRender();
			}

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
