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

			int ppu = 100; // ppu

			Drawable* drawable = nullptr;

			__Layer layer = Layers::DEFAULT_LAYER;
			int orderInLayer = 0;

			bool render = true;
		};

		class TextObject : public RenderObject
		{
		public:

			TextObject(int _ppu, string _string, Color _color);
			TextObject(const TextObject& that);

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

			SpriteObject(int _ppu, string _spritePath);
			SpriteObject(const SpriteObject& that);

			string spritePath;

			Texture texture;
			Sprite sprite;

			void SetSprite(string _spritePath);
			Vector2f GetSize();
		};
	}
}

#endif // !RENDER_OBJECT_H
