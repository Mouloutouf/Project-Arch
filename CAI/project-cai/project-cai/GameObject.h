#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "SpriteRenderer.h"
#include "Behaviour.h"

class SpriteRenderer;
class Behaviour;

class GameObject
{
public:

	GameObject();
	GameObject(SpriteRenderer * newSpriteRenderer, float scale);
	GameObject(SpriteRenderer * newSpriteRenderer, float scale, vector<Behaviour *> attachedBehaviours);
	virtual ~GameObject();

	virtual void Start();

	virtual void Update(float elapsedTime);
	virtual void Render(RenderWindow * window);

	SpriteRenderer * spriteRenderer;

	Vector2f position;

	vector<Behaviour *> behaviours;
};

#endif // !GAME_OBJECT_H
