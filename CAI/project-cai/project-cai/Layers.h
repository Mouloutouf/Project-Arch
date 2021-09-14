#pragma once

#ifndef LAYERS_H
#define LAYERS_H

#include "Alpha.h"

namespace alpha
{
	namespace core
	{
#define __Layer int

		class Layers
		{
		public:
			static const __Layer DEFAULT_LAYER = 0;

			static const __Layer ENVIRONMENT_LAYER = 10000;
			static const __Layer ELEMENTS_LAYER = 20000;
			static const __Layer DETAILS_LAYER = 30000;

			static const __Layer UI_LAYER = 40000;
		};
	}
}

#endif // !LAYERS_H
