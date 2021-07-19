#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "Component.h"
#include "GameObject.h"

class Component;
class GameObject;
struct Transform2D;

class SpriteRenderer : public Component
{
public:

	SpriteRenderer(); SpriteRenderer(GameObject* _gameObject, string _spritePath = nullptr);
	~SpriteRenderer();

	void Update(float _elapsedTime) override;
	void Draw(RenderWindow* _window) override;

	Vector2f GetSize();

	void SetPosition(Vector2f _pos);

	void SetScale(float _scale);
	void SetScale(Vector2f _scale);

	void SetRotation(float _angle);

protected:

	string spritePath;

	Sprite sprite;
	Texture texture;

	Vector2f centerPosition;
};

#endif // !SPRITE_RENDERER_H
