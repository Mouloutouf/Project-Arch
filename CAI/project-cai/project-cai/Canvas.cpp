#include "Canvas.h"

namespace alpha
{
	namespace core
	{
		Canvas::Canvas()
		{
		}
		Canvas::Canvas(GameObject* _gameObject)
			: Component(_gameObject), transform(static_cast<UITransform*>(_gameObject->transform))
		{
		}
		Canvas::Canvas(GameObject* _gameObject, RenderSpace _renderSpace, Display* _display)
			: Component(_gameObject), transform(static_cast<UITransform*>(_gameObject->transform)), renderSpace(_renderSpace), display(_display)
		{
			transform->renderMode = _renderSpace;

			if (renderSpace == RenderSpace::ScreenSpace)
				transform->SetSize(display->gameWindow->width, display->gameWindow->height);
		}
		Canvas::Canvas(const Canvas& that, GameObject* _gameObject)
			: Component(that, _gameObject), transform(static_cast<UITransform*>(_gameObject->transform)), renderSpace(that.renderSpace)
		{
		}

		Canvas::~Canvas()
		{
		}

		Canvas* Canvas::Clone(GameObject* _gameObject)
		{
			return new Canvas(*this, _gameObject);
		}
	}
}
