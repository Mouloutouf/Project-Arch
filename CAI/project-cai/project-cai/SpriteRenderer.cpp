#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(string imagePath)
{
	texture = new Texture();
	sprite = new Sprite();

	texture->loadFromFile(imagePath);
	
	sprite->setTexture(*texture);
	FloatRect rect;
	IntRect pixelRect;

	SetPosition(position);
}

SpriteRenderer::~SpriteRenderer()
{
	delete sprite;

	delete texture;
}

void SpriteRenderer::Render(RenderWindow * window)
{
	window->draw(*sprite);
}

void SpriteRenderer::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	sprite->setPosition(position);
}

void SpriteRenderer::SetPosition(Vector2f pos)
{
	position = pos;

	sprite->setPosition(position);
}

Vector2f SpriteRenderer::GetSpriteSize()
{
	return (Vector2f)texture->getSize();
}

void SpriteRenderer::SetScale(float scale)
{
	sprite->setScale(sprite->getScale().x * scale, sprite->getScale().y * scale);
}

void SpriteRenderer::SetRotation(float angle)
{
	sprite->setRotation(angle);
}
