#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Alpha.h"

///\

#include "Utility.h"

#include "GameWindow.h"

#include "Camera.h"

namespace alpha
{
	namespace core
	{
		class RenderedObject
		{
		public:

			RenderedObject();
			RenderedObject(GameObject* _gameObject, Sprite* _sprite, int _ppu, Camera* _cam, Vector2f _origin);
			~RenderedObject();

			void CalculateDraw();

			GameObject* objectToRender;
			Sprite* spriteToRender;
			int spritePixelsPerUnit;
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

			void AddObjectToRender(GameObject* _gameObject, Sprite* _sprite, int _ppu);
			void RemoveObjectToRender(GameObject* _gameObject);

			void Render();
			void Draw(Sprite* _sprite);

			void DebugDraw(RenderedObject* _rd);

			void DrawBackground();

			void DrawGrid();

			Vector2f resolution;
			Vector2f displayOrigin() { return resolution / 2.0f; }

			Camera* camera;

		private:

			GameWindow* gameWindow;

			vector<GameObject*> objectsToRender;
			
			vector<RenderedObject*> renderedObjects;

			int ContainsObjectToRender(GameObject* _gameObject);

			Vector2f worldOrigin() {
				Vector2f origin = -(camera->gameObject->transform.position());
				origin *= (float)camera->pixelsPerUnit();
				origin = Vector2f(displayOrigin().x + origin.x, displayOrigin().y - origin.y);
				return origin;
			}
		};
	}
}

#endif // !DISPLAY_H
