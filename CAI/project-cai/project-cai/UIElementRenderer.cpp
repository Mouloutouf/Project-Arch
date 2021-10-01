#include "UIElementRenderer.h"

namespace alpha
{
	namespace core
	{
		UISpriteRenderer::UISpriteRenderer()
		{
		}
		UISpriteRenderer::UISpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu, __Layer _layer)
		{
			gameObject = _gameObject;

			display = _display;

			spriteObject = new UISpriteObject(_ppu, _spritePath);
			spriteObject->layer = _layer;

			uiSpriteObject = dynamic_cast<UISpriteObject*>(spriteObject);

			AddToRender();
		}
		UISpriteRenderer::UISpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu, __Layer _layer)
		{
			gameObject = _gameObject;

			display = _display;

			spriteObject = new UISpriteObject(_ppu, _texture);
			spriteObject->layer = _layer;

			uiSpriteObject = dynamic_cast<UISpriteObject*>(spriteObject);

			AddToRender();
		}
		UISpriteRenderer::UISpriteRenderer(const UISpriteRenderer& that, GameObject* _gameObject)
		{
			gameObject = _gameObject;

			display = that.display;

			spriteObject = new UISpriteObject(*dynamic_cast<UISpriteObject*>(that.spriteObject));

			uiSpriteObject = dynamic_cast<UISpriteObject*>(spriteObject);

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
	}
}
