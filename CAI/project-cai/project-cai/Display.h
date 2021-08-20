#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Alpha.h"

///\

#include "Utility.h"

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

			void Setup(vector<SpriteRenderer*> _srs, Camera* _camera);

			void AddObjectToRender(SpriteRenderer* _sr);
			void RemoveObjectToRender(SpriteRenderer* _sr);

			void Render();
			void Draw(Sprite* _sprite);

			void DebugDraw(RenderedObject* _rd);

			void DrawBackground();

			void DrawGrid();

			Vector2f resolution;
			Vector2f displayOrigin() { return resolution / 2.0f; }

		private:

			GameWindow* gameWindow;

			vector<SpriteRenderer*> renderers;
			Camera* camera;

			vector<RenderedObject> renderedObjects;

			int ContainsObjectToRender(SpriteRenderer* _sr);

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
