#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class SpriteRenderer
{
public:

	SpriteRenderer(string imagePath);
	~SpriteRenderer();

	void Render(RenderWindow * window);

	void SetPosition(float x, float y);
	void SetPosition(Vector2f pos);

	Vector2f GetSpriteSize();

	void SetScale(float scale);

	void SetRotation(float angle);

protected:

	Sprite * sprite;
	Texture * texture;

	Vector2f position;
};

#endif // !SPRITE_RENDERER_H
