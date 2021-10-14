#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

#include "RenderObject.h"
#include "Display.h"

#include "Renderer.h"

namespace alpha
{
	namespace core
	{
		class SpriteRenderer : public Component
		{
		public:

			// Sprite Renderer uses GameObject in its constructor as it needs to know wether the object is a prefab or not in order to add itself to the render
			SpriteRenderer();
			SpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			SpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
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

		class _SpriteRenderer : public Renderer<SpriteObject>
		{
			// Sprite Renderer uses GameObject in its constructor as it needs to know wether the object is a prefab or not in order to add itself to the render
			_SpriteRenderer();
			_SpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			_SpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			_SpriteRenderer(const _SpriteRenderer& that, GameObject* _gameObject);
			
			~_SpriteRenderer();
			
			_SpriteRenderer* Clone(GameObject* _gameObject) override;

			Vector2f GetSize();

			string GetSpritePath();

			void SetSprite(string _spritePath);
			void SetSprite(Texture _texture);

			Sprite* GetSprite();

		protected:

			SpriteObject* spriteObject = dynamic_cast<SpriteObject*>(renderObject);
		};
	}
}

#endif // !SPRITE_RENDERER_H
