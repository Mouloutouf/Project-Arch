#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameObject.h"
#include "Component.h"

class SpriteRenderer : public Component
{
public:

	SpriteRenderer(); SpriteRenderer(GameObject* _gameObject, string _spritePath = nullptr);
	~SpriteRenderer();

	Vector2f GetSize();
	Sprite* GetSprite();

	int ppu;

protected:

	string spritePath;

	Sprite sprite;
	Texture texture;
};

#endif // !SPRITE_RENDERER_H
