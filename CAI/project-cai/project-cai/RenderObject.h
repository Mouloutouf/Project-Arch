#pragma once

#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "Alpha.h"

///\

#include "Utility.h"
#include "Layers.h"

namespace alpha
{
	namespace core
	{
		class RenderObject
		{
		public:

			RenderObject(int _ppu);

			virtual void Create(int _ppu) = 0;

			int ppu = 100; // ppu

			vector<Drawable*> drawables;

			__Layer layer = Layers::DEFAULT_LAYER;
			int orderInLayer = 0;

			bool render = true;
		};

		class TextObject : public RenderObject
		{
		public:

			TextObject(int _ppu);
			TextObject(int _ppu, string _string, Color _color);
			TextObject(const TextObject& that);

			Color color;
			string string;
			Font font;

			Text text;

			void Create(int _ppu) override;
			void Create(int _ppu, std::string _string, Color _color);

			void SetString(std::string _string);
			void SetCharacterSize(int _size);
			void SetColor(Color _color);
		};

		class SpriteObject : public RenderObject
		{
		public:

			SpriteObject(int _ppu);
			SpriteObject(int _ppu, string _spritePath);
			SpriteObject(int _ppu, Texture _texture);
			SpriteObject(const SpriteObject& that);

			void Create(int _ppu) override;
			void Create(int _ppu, string _spritePath);
			void Create(int _ppu, Texture _texture);

			string spritePath;

			Texture texture;
			Sprite sprite;

			void SetSprite(string _spritePath);
			void SetSprite(Texture _texture);
			Vector2f GetSize();
		};

		class UISpriteObject : public SpriteObject
		{
		public:

			UISpriteObject(int _ppu, string _spritePath);
			UISpriteObject(int _ppu, Texture _texture);
			UISpriteObject(const UISpriteObject& that);

			RectangleShape shape;

			float outlineThickness = 0.0f;
			Color outlineColor = Color::White;

			void SetOutline(float _thickness, Color _color);
			bool HasOutline();

			void SetColor(Color _color);
		};
	}
}

#endif // !RENDER_OBJECT_H
