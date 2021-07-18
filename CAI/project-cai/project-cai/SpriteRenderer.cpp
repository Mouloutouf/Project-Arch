#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}
SpriteRenderer::SpriteRenderer(GameObject* _gameObject, string _spritePath)
: spritePath(_spritePath)
{
	Component(_gameObject);

	texture = Texture();
	sprite = Sprite();

	if (!_spritePath.empty())
	{
		texture.loadFromFile(_spritePath);

		sprite.setTexture(texture);
		/*FloatRect rect;
		IntRect pixelRect;*/

		centerPosition = Vector2f(texture.getSize() / 2u);
	}
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Update(float _elapsedTime)
{
	SetPosition(gameObject->transform.position());
}

void SpriteRenderer::Draw(RenderWindow * _window)
{
	_window->draw(sprite);
}

void SpriteRenderer::SetPosition(Vector2f _position)
{
	sprite.setPosition(_position - centerPosition);
}

Vector2f SpriteRenderer::GetSize()
{
	return Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
}

void SpriteRenderer::SetScale(float _scale)
{
	sprite.setScale(sprite.getScale().x * _scale, sprite.getScale().y * _scale);
}
void SpriteRenderer::SetScale(Vector2f _scale)
{
	sprite.setScale(sprite.getScale().x * _scale.x, sprite.getScale().y * _scale.y);
}

void SpriteRenderer::SetRotation(float _angle)
{
	sprite.setRotation(_angle);
}
