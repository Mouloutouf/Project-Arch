#pragma once

#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "Alpha.h"

///\

#include "Layers.h"

namespace alpha
{
	namespace core
	{
		struct _TextObject
		{
			Color color;
			string string;
			Font font;

			Text text;

			int characterSize = 1; // ppu

			__Layer layer;
			int orderInLayer;

			bool render = true;
		};
	}
}

#endif // !TEXT_OBJECT_H
