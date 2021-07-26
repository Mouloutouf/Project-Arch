#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "SpriteRenderer.h"
#include "Camera.h"

class RenderedObject
{
public:

	RenderedObject(); // Ctor
	//RenderedObject(Sprite* _sprite, Vector2f _sPos, Vector2f _cPos, int _cppu, Vector2i _wPos, Vector2f _sScale, int _sppu);
	RenderedObject(SpriteRenderer* _sr, Camera* _cam, Vector2i _origin);
	~RenderedObject();

	void Draw();

	Sprite* sprite;

	SpriteRenderer* sr;
	Camera* cam;
	Vector2i origin;

	//Vector2f rwPos; // Relative World Position -> position in units relative to camera
	//Vector2i rdPos; // Relative Display Position -> conversion to pixel position based of the camera pixels per unit
	//Vector2i dPos; // Display Position -> center the position to the origin of the display

	//Vector2f dScale; // Display Scale -> size of the rendered object
};

struct Display
{
	Display();
	Display(Vector2i _resolution);
	Display(int resX, int resY);
	~Display();

	Vector2i resolution;
	Vector2i origin() { return resolution / 2; }

	void Setup(vector<SpriteRenderer*> _spriteObjects, Camera* _cameraObject);
	void AddObjectToRender(SpriteRenderer* _spriteObject);
	void RemoveObjectToRender(SpriteRenderer* _spriteObject);

	void Render();

private:

	vector<SpriteRenderer*> spriteObjects;
	Camera* cameraObject;

	vector<RenderedObject> renderedObjects;

	int ContainsSpriteObject(SpriteRenderer* _spriteObject);
};

#endif // !DISPLAY_H
