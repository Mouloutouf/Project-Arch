#include "SpriteRenderer.h"

namespace alpha
{
	namespace core
	{
		SpriteRenderer::SpriteRenderer()
		{
		}
		SpriteRenderer::SpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu, __Layer _layer)
			: Component(_gameObject), display(_display)
		{
			spriteObject = new SpriteObject(_ppu, _spritePath);
			spriteObject->layer = _layer;

			AddToRender();
		}
		SpriteRenderer::SpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu, __Layer _layer)
			: Component(_gameObject), display(_display)
		{
			spriteObject = new SpriteObject(_ppu, _texture);
			spriteObject->layer = _layer;

			AddToRender();
		}
		SpriteRenderer::SpriteRenderer(const SpriteRenderer& that, GameObject* _gameObject)
			: Component(that, _gameObject), display(that.display)
		{
			spriteObject = new SpriteObject(*that.spriteObject);

			AddToRender();
		}

		SpriteRenderer::~SpriteRenderer()
		{
			delete spriteObject;
		}

		void SpriteRenderer::AddToRender()
		{
			auto& tags = *(gameObject->GetTagsList());
			for (int i = 0; i < tags.size(); i++) {
				if (tags[i] == Tag::Prefab)
					return;
			} display->AddObjectToRender(gameObject, spriteObject);
		}

		SpriteRenderer* SpriteRenderer::Clone(GameObject* _gameObject)
		{
			return new SpriteRenderer(*this, _gameObject);
		}

		void SpriteRenderer::SetActive(bool _value)
		{
			Component::SetActive(_value);
			spriteObject->render = _value;
		}

		Vector2f SpriteRenderer::GetSize() { return spriteObject->GetSize(); }

		void SpriteRenderer::SetLayer(__Layer _layer)
		{
			spriteObject->layer = _layer;

			display->RemoveObjectToRender(spriteObject);
			AddToRender();
		}
		__Layer SpriteRenderer::GetLayer() { return spriteObject->layer; }

		void SpriteRenderer::SetOrderInLayer(int _order) { spriteObject->orderInLayer = clamp(_order, 0, 9999); }
		int SpriteRenderer::GetOrderInLayer() { return spriteObject->orderInLayer; }

		string SpriteRenderer::GetSpritePath() { return spriteObject->spritePath; }

		void SpriteRenderer::SetSprite(string _spritePath) { spriteObject->SetSprite(_spritePath); }
		Sprite* SpriteRenderer::GetSprite() { return &spriteObject->sprite; }

		/// Sprite Renderer T

		_SpriteRenderer::_SpriteRenderer()
		{
		}
		_SpriteRenderer::_SpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu, __Layer _layer)
			: Renderer<SpriteObject>(_gameObject, _display, _ppu, _layer)
		{
			spriteObject = dynamic_cast<SpriteObject*>(renderObject);
			SetSprite(_spritePath);
		}
		_SpriteRenderer::_SpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu, __Layer _layer)
			: Renderer<SpriteObject>(_gameObject, _display, _ppu, _layer)
		{
			spriteObject = dynamic_cast<SpriteObject*>(renderObject);
			SetSprite(_texture);
		}
		_SpriteRenderer::_SpriteRenderer(const _SpriteRenderer& that, GameObject* _gameObject)
			: Renderer<SpriteObject>(that, _gameObject)
		{
			spriteObject = dynamic_cast<SpriteObject*>(renderObject);
		}

		_SpriteRenderer::~_SpriteRenderer()
		{
		}

		_SpriteRenderer* _SpriteRenderer::Clone(GameObject* _gameObject)
		{
			return new _SpriteRenderer(*this, _gameObject);
		}

		Vector2f _SpriteRenderer::GetSize() { return spriteObject->GetSize(); }

		string _SpriteRenderer::GetSpritePath() { return spriteObject->spritePath; }

		void _SpriteRenderer::SetSprite(string _spritePath) { spriteObject->SetSprite(_spritePath); }
		void _SpriteRenderer::SetSprite(Texture _texture) { spriteObject->SetSprite(_texture); }

		Sprite* _SpriteRenderer::GetSprite() { return &spriteObject->sprite; }
	}
}
