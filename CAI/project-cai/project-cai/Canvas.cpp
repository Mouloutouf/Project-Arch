#include "Canvas.h"

namespace alpha
{
	namespace core
	{
		UITransform* UITransform::Clone()
		{
			return new UITransform(*this);
		}

		Canvas::Canvas()
		{
		}
		
	}
}
