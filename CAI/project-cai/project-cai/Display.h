#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameWindow.h"

#include "SpriteRenderer.h"
#include "Camera.h"

class RenderedObject
{
public:

	RenderedObject(); // Ctor
	//RenderedObject(Sprite* _sprite, Vector2f _sPos, Vector2f _cPos, int _cppu, Vector2i _wPos, Vector2f _sScale, int _sppu);
	RenderedObject(SpriteRenderer* _sr, Camera* _cam, Vector2f _origin);
	~RenderedObject();

	void CalculateDraw();

	Sprite* sprite;

	SpriteRenderer* spriteRenderer;
	Camera* cam;
	Vector2f origin;

	Vector2f cachedDisplayPos; // -> World position, center of the sprite is (0, 0)
	Vector2f cachedDrawPos; // -> Draw Position, top-left corner of the sprite is (0, 0), same position as above but with offset from the center to match the origin
	Vector2f cachedDisplayScale;

	//Vector2f rwPos; // Relative World Position -> position in units relative to camera
	//Vector2i rdPos; // Relative Display Position -> conversion to pixel position based of the camera pixels per unit
	//Vector2i dPos; // Display Position -> center the position to the origin of the display

	//Vector2f dScale; // Display Scale -> size of the rendered object
};

struct Display
{
	Display();
	Display(Vector2f _resolution, GameWindow* _gameWindow);
	Display(int resX, int resY, GameWindow* _gameWindow);
	~Display();

	Vector2f resolution;
	Vector2f origin() { return resolution / 2.0f; }

	void Setup(vector<SpriteRenderer*> _spriteObjects, Camera* _cameraObject);
	void AddObjectToRender(SpriteRenderer* _spriteObject);
	void RemoveObjectToRender(SpriteRenderer* _spriteObject);

	void Render();
	void Draw(Sprite* _sprite);
	void DebugDraw(RenderedObject* _rd);

	void DrawGrid();

private:

	GameWindow* gameWindow;

	vector<SpriteRenderer*> spriteObjects;
	Camera* cameraObject;

	vector<RenderedObject> renderedObjects;

	int ContainsSpriteObject(SpriteRenderer* _spriteObject);
};

#endif // !DISPLAY_H
