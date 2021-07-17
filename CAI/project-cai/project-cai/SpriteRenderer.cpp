#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
	Component();
}
SpriteRenderer::SpriteRenderer(GameObject* _gameObject, string _name = nullptr, string _spritePath = nullptr)
: spritePath(_spritePath)
{
	Component(_gameObject, _name);

	texture = Texture();
	sprite = Sprite();

	if (!_spritePath.empty())
	{
		texture.loadFromFile(_spritePath);

		sprite.setTexture(texture);
		/*FloatRect rect;
		IntRect pixelRect;*/
	}

	SetPosition(position);
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Draw(RenderWindow * _window)
{
	_window->draw(sprite);
}

void SpriteRenderer::SetPosition(float _x, float _y)
{
	position.x = _x;
	position.y = _y;

	sprite.setPosition(position);
}
void SpriteRenderer::SetPosition(Vector2f _position)
{
	position = _position;

	sprite.setPosition(position);
}

Vector2f SpriteRenderer::GetSpriteSize()
{
	return (Vector2f)texture.getSize();
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
