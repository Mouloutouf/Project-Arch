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

			RenderObject();
			RenderObject(int _ppu);
			virtual ~RenderObject();

			int ppu = 100;

			__Layer layer = Layers::DEFAULT_LAYER;
			int orderInLayer = 0;

			bool render = true;

			vector<Drawable*> drawables;
		};

		class TextObject : public RenderObject
		{
		public:

			TextObject(int _ppu, string _string = "New Text", Color _color = Color::White);
			TextObject(const TextObject& that);
			virtual ~TextObject();

			void Create(string _string, Color _color);

			Color color;
			string string;
			Font font;

			Text text;

			void SetString(std::string _string);
			void SetCharacterSize(int _size);
			void SetColor(Color _color);
		};

		class SpriteObject : public RenderObject
		{
		public:

			SpriteObject();
			SpriteObject(int _ppu, string _spritePath = DEFAULT_SPRITE);
			SpriteObject(int _ppu, Texture _texture);
			SpriteObject(const SpriteObject& that);
			virtual ~SpriteObject();

			void Create(string _spritePath);
			void Create(Texture _texture);

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

			UISpriteObject(int _ppu, string _spritePath = string());
			UISpriteObject(int _ppu, Texture _texture);
			UISpriteObject(const UISpriteObject& that);
			virtual ~UISpriteObject();

			void Create(string _spritePath);
			void Create(Texture _texture);

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
