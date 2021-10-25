#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Alpha.h"

///\

#include "Utility.h"
#include "GameWindow.h"

#include "Camera.h"

#include "RenderObject.h"

#include "UITransform.h"

namespace alpha
{
	namespace core
	{
		class DisplayedObject
		{
		public:

			DisplayedObject(GameObject* _gameObject, RenderObject* _renderObject, Camera* _cam, Vector2f _origin);
			~DisplayedObject();

			void CalculateDraw();

			GameObject* gameObjectToRender;

			RenderObject* objectToRender = nullptr;
			bool isUI;
			bool isText;

			int ppu;
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

			void AddObjectToRender(GameObject* _gameObject, RenderObject* _renderObject);
			void RemoveObjectToRender(RenderObject* _renderObject);

			void Render();
			void Draw(Drawable* _drawable, DisplayedObject* _d);

			void DebugDraw(DisplayedObject* _rd);

			void DrawBackground();

			void DrawGrid();

			Vector2f ScreenToWorldPosition(Vector2f _screenPosition);
			Vector2f WorldToScreenPosition(Vector2f _worldPosition);
			Vector2f MousePositionToWorld();

			void SetBackgroundColor(Color _color);
			Color BackgroundColor();

			Vector2f resolution;
			Vector2f displayOrigin() { return resolution / 2.0f; }

			Camera* camera = nullptr;
			GameWindow* gameWindow = nullptr;

		private:

			vector<int> entries;
			map<int, vector<DisplayedObject*>> displayedObjects;

			int FindKeyPosition(int _newKey);

			pair<int, int> ContainsObjectToRender(RenderObject* _renderObject);

			Vector2f worldOrigin() {
				Vector2f origin = -(camera->gameObject->transform->position());
				origin *= (float)camera->pixelsPerUnit();
				origin = Vector2f(displayOrigin().x + origin.x, displayOrigin().y - origin.y);
				return origin;
			}

			Color backgroundColor = BACKGROUND_COLOR;
		};
	}
}

#endif // !DISPLAY_H
