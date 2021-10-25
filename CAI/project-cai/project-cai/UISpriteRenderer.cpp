#include "UISpriteRenderer.h"

namespace alpha
{
	namespace core
	{
		UISpriteRenderer::UISpriteRenderer()
		{
		}
		UISpriteRenderer::UISpriteRenderer(GameObject* _gameObject, Display* _display, __Layer _layer, string _spritePath, int _ppu)
		{
			gameObject = _gameObject;

			display = _display;

			spriteObject = new UISpriteObject(_ppu, _spritePath);
			spriteObject->layer = _layer;

			uiSpriteObject = static_cast<UISpriteObject*>(spriteObject);

			AddToRender();
		}
		UISpriteRenderer::UISpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, __Layer _layer, int _ppu)
		{
			gameObject = _gameObject;

			display = _display;

			spriteObject = new UISpriteObject(_ppu, _texture);
			spriteObject->layer = _layer;

			uiSpriteObject = static_cast<UISpriteObject*>(spriteObject);

			AddToRender();
		}
		UISpriteRenderer::UISpriteRenderer(const UISpriteRenderer& that, GameObject* _gameObject)
		{
			gameObject = _gameObject;

			display = that.display;

			spriteObject = new UISpriteObject(*static_cast<UISpriteObject*>(that.spriteObject));

			uiSpriteObject = static_cast<UISpriteObject*>(spriteObject);

			AddToRender();
		}

		UISpriteRenderer::~UISpriteRenderer()
		{
		}

		UISpriteRenderer* UISpriteRenderer::Clone(GameObject* _gameObject)
		{
			return new UISpriteRenderer(*this, _gameObject);
		}

		void UISpriteRenderer::SetOutline(float _thickness, Color _color) { uiSpriteObject->SetOutline(_thickness, _color); }
		bool UISpriteRenderer::HasOutline() { return uiSpriteObject->HasOutline(); }

		void UISpriteRenderer::SetColor(Color _color) { uiSpriteObject->SetColor(_color); }
	}
}
