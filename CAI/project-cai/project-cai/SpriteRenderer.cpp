#include "SpriteRenderer.h"

namespace alpha
{
	namespace core
	{
		SpriteRenderer::SpriteRenderer()
		{
		}
		SpriteRenderer::SpriteRenderer(GameObject* _gameObject, Display* _display, string _spritePath, int _ppu)
			: Component(_gameObject), spritePath(_spritePath), pixelsPerUnit(_ppu), display(_display)
		{
			texture = Texture();
			sprite = Sprite();

			if (!_spritePath.empty())
			{
				texture.loadFromFile(_spritePath);

				sprite.setTexture(texture);
			}

			AddToRender();
		}
		SpriteRenderer::SpriteRenderer(const SpriteRenderer& that, GameObject* _gameObject)
			: Component(that, _gameObject), sprite(that.sprite), texture(that.texture), spritePath(that.spritePath), pixelsPerUnit(that.pixelsPerUnit), display(that.display)
		{
			sprite.setTexture(texture);

			AddToRender();
		}

		SpriteRenderer::~SpriteRenderer()
		{
		}

		void SpriteRenderer::AddToRender()
		{
			auto& tl = *gameObject->GetTagsList();
			for (int i = 0; i < tl.size(); i++) {
				if (tl[i] == Tag::Prefab)
					return;
			} display->AddObjectToRender(gameObject, &sprite, pixelsPerUnit);
		}

		SpriteRenderer* SpriteRenderer::Clone(GameObject* _gameObject)
		{
			return new SpriteRenderer(*this, _gameObject);
		}

		Vector2f SpriteRenderer::GetSize()
		{
			return Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
		}

		Sprite* SpriteRenderer::GetSprite()
		{
			return &sprite;
		}
	}
}
