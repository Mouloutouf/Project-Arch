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

namespace alpha
{
	namespace core
	{
		class RenderedObject
		{
		public:

			RenderedObject();
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
		};

		struct Display
		{
			Display();
			Display(Vector2f _resolution, GameWindow* _gameWindow);
			Display(int resX, int resY, GameWindow* _gameWindow);
			~Display();

			Vector2f resolution;
			Vector2f displayOrigin() { return resolution / 2.0f; }

			void Setup(vector<SpriteRenderer*> _srs, Camera* _camera);
			void AddObjectToRender(SpriteRenderer* _sr);
			void RemoveObjectToRender(SpriteRenderer* _sr);

			void Render();
			void Draw(Sprite* _sprite);
			void DebugDraw(RenderedObject* _rd);

			void DrawBackground();
			void DrawGrid();

			int powerOf(float _value, int _base) {
				int r = 0;
				while (_value >= _base) { _value /= _base; ++r; }
				return r;
			}
			float pceil(float _value, int _base) {
				float mod = (float)fmod(_value, _base);
				_value += (_value > 0 ? _base : 0 - mod);
				return _value;
			}
			float pfloor(float _value, int _base) {
				float mod = _value > 0 ? (float)fmod(_value, _base) : (float)fmod(_base, _value);
				_value -= mod;
				return _value;
			}

		private:

			GameWindow* gameWindow;

			vector<SpriteRenderer*> spriteObjects;
			Camera* cameraObject;

			vector<RenderedObject> renderedObjects;

			int ContainsObjectToRender(SpriteRenderer* _sr);

			Vector2f worldOrigin() {
				Vector2f origin = -(cameraObject->gameObject->transform.position());
				origin *= (float)cameraObject->ppu();
				origin = Vector2f(displayOrigin().x + origin.x, displayOrigin().y - origin.y);
				return origin;
			}

			Color backgroundColor = Color(43, 46, 59);
			Color detailColor = Color(67, 82, 104);
			Color greenColor = Color(131, 255, 70);

			Color redColor = Color(255, 55, 55);
			Color blueColor = Color(44, 135, 255);
		};
	}
}

#endif // !DISPLAY_H
