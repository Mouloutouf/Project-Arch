#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "Component.h"

using namespace std;
using namespace sf;

class SpriteRenderer : public Component
{
public:

	SpriteRenderer();
	SpriteRenderer(GameObject* _gameObject, string _name = nullptr, string _spritePath = nullptr);
	~SpriteRenderer();

	void Draw(RenderWindow * _window);

	void SetPosition(float _x, float _y);
	void SetPosition(Vector2f _pos);

	Vector2f GetSpriteSize();

	void SetScale(float _scale);
	void SetScale(Vector2f _scale);

	void SetRotation(float _angle);

protected:

	string spritePath;

	Sprite sprite;
	Texture texture;

	Vector2f position;
};

#endif // !SPRITE_RENDERER_H
