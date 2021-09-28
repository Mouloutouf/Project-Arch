#include "UIElementRenderer.h"

namespace alpha
{
	namespace core
	{
		UISpriteRenderer::UISpriteRenderer()
		{
		}
		UISpriteRenderer::UISpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu, __Layer _layer)
			: SpriteRenderer(_gameObject, _display, _spritePath, _ppu, _layer)
		{
		}
		UISpriteRenderer::UISpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu, __Layer _layer)
			: SpriteRenderer(_gameObject, _display, _texture, _ppu, _layer)
		{
		}
		UISpriteRenderer::UISpriteRenderer(const UISpriteRenderer& that, GameObject* _gameObject)
			: SpriteRenderer(that, _gameObject)
		{
		}
		UISpriteRenderer::~UISpriteRenderer()
		{
		}
		UISpriteRenderer* UISpriteRenderer::Clone(GameObject* _gameObject)
		{
			return nullptr;
		}
		void UISpriteRenderer::CreateRenderObject(string _spritePath, int _ppu, __Layer _layer)
		{
			spriteObject = new UISpriteObject(_ppu, _spritePath);
			spriteObject->layer = _layer;

			AddToRender();
		}
		void UISpriteRenderer::CreateRenderObject(Texture _texture, int _ppu, __Layer _layer)
		{
			spriteObject = new UISpriteObject(_ppu, _texture);
			spriteObject->layer = _layer;

			AddToRender();
		}
	}
}
