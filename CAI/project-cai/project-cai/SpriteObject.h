#pragma once

#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "Alpha.h"

///\

#include "Layers.h"

namespace alpha
{
	namespace core
	{
		struct _SpriteObject
		{
			string spritePath;

			Texture texture;
			Sprite sprite;

			int pixelsPerUnit = 1;

			__Layer layer;
			int orderInLayer;

			bool render = true;
		};
	}
}

#endif // !SPRITE_OBJECT_H
