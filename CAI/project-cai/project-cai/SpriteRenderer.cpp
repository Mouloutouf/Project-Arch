#include "SpriteRenderer.h"

namespace alpha
{
	namespace core
	{
		SpriteRenderer::SpriteRenderer()
		{
		}
		SpriteRenderer::SpriteRenderer(GameObject* _gameObject, Display* _display)
			: Component(_gameObject), display(_display)
		{
		}
		SpriteRenderer::SpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu, __Layer _layer)
			: Component(_gameObject), display(_display)
		{
			CreateRenderObject(_spritePath, _ppu, _layer);
		}
		SpriteRenderer::SpriteRenderer(GameObject* _gameObject, Display* _display, Texture _texture, int _ppu, __Layer _layer)
			: Component(_gameObject), display(_display)
		{
			CreateRenderObject(_texture, _ppu, _layer);
		}
		SpriteRenderer::SpriteRenderer(const SpriteRenderer& that, GameObject* _gameObject)
			: Component(that, _gameObject), display(that.display)
		{
			// Will not work for when passing a UISpriteObject* as a SpriteObject*
			// The substitued T type will still be a SpriteObject*
			// Polymorphims and templates do not mix. Which is a great fucking shame.
			CreateRenderObject(that.spriteObject);
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

		void SpriteRenderer::CreateRenderObject(string _spritePath, int _ppu, __Layer _layer)
		{
			spriteObject = new SpriteObject(_ppu, _spritePath);
			spriteObject->layer = _layer;

			AddToRender();
		}
		void SpriteRenderer::CreateRenderObject(Texture _texture, int _ppu, __Layer _layer)
		{
			spriteObject = new SpriteObject(_ppu, _texture);
			spriteObject->layer = _layer;

			AddToRender();
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
	}
}
