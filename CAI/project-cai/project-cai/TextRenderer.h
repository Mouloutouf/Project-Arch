#pragma once

#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

#include "Display.h"

namespace alpha
{
	namespace core
	{
		class TextRenderer : public Component
		{
		public:

			TextRenderer();
			TextRenderer(GameObject* _gameObject, Display* _display, string _string = "", Color _color = Color::White, int _characterSize = 1);
			TextRenderer(const TextRenderer& that, GameObject* _gameObject);
			~TextRenderer();

			TextRenderer* Clone(GameObject* _gameObject) override;

			void AddToRender();

			void setString(string _string) { string = _string; }

			int characterSize = 1; // ppu

		protected:

			Color color;
			string string;
			Font font;
			Text text;

			Display* display = nullptr;
		};
	}
}

#endif // !TEXT_RENDERER_H
