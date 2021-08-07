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

	SpriteRenderer();
	SpriteRenderer(GameObject* _gameObject, string _spritePath = nullptr, int _ppu = 1);
	SpriteRenderer(const SpriteRenderer& that);
	~SpriteRenderer();

	SpriteRenderer* Clone() override;

	Vector2f GetSize();
	Sprite* GetSprite();

	int pixelsPerUnit = 1;

protected:

	string spritePath;

	Sprite sprite;
	Texture texture;
};

#endif // !SPRITE_RENDERER_H
