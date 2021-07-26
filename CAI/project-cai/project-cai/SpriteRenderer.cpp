#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}
SpriteRenderer::SpriteRenderer(GameObject* _gameObject, string _spritePath)
: Component(_gameObject), spritePath(_spritePath)
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

SpriteRenderer::~SpriteRenderer()
{
}

Vector2f SpriteRenderer::GetSize()
{
	return Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
}

Sprite* SpriteRenderer::GetSprite()
{
	return &sprite;
}
