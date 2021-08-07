#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}
SpriteRenderer::SpriteRenderer(GameObject* _gameObject, string _spritePath, int _ppu)
	: Component(_gameObject), spritePath(_spritePath), pixelsPerUnit(_ppu)
{
	texture = Texture();
	sprite = Sprite();

	if (!_spritePath.empty())
	{
		texture.loadFromFile(_spritePath);

		sprite.setTexture(texture);
		/*FloatRect rect;
		IntRect pixelRect;*/

		//centerPosition = Vector2f(texture.getSize() / 2u);
	}
}
SpriteRenderer::SpriteRenderer(const SpriteRenderer& that)
	: Component(that), sprite(that.sprite), texture(that.texture), spritePath(that.spritePath), pixelsPerUnit(that.pixelsPerUnit)
{
	sprite.setTexture(texture);
}

SpriteRenderer::~SpriteRenderer()
{
}

SpriteRenderer* SpriteRenderer::Clone()
{
	return new SpriteRenderer(*this);
}

Vector2f SpriteRenderer::GetSize()
{
	return Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
}

Sprite* SpriteRenderer::GetSprite()
{
	return &sprite;
}
