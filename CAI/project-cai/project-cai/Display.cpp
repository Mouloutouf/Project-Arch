#include "Display.h"

namespace alpha
{
	namespace core
	{
		/// Rendered Object
		///
#pragma region RenderedObject
		RenderedObject::RenderedObject(GameObject* _gameObject, Sprite* _sprite, int _ppu, Camera* _cam, Vector2f _origin)
			: objectToRender(_gameObject), spriteToRender(_sprite), spritePixelsPerUnit(_ppu), cam(_cam), origin(_origin)
		{
		}

		RenderedObject::~RenderedObject()
		{
		}

		void RenderedObject::CalculateDraw()
		{
			/// Position
			Vector2f pos;
			pos = objectToRender->transform.position() - cam->gameObject->transform.position(); // Calculate the position of the sprite relative to the camera
			pos *= (float)cam->pixelsPerUnit(); // Convert the position from units to pixels
			pos = Vector2f(origin.x + pos.x, origin.y - pos.y); // Calculate the position relative to the origin of the display (and not the top left corner)

			cachedDisplayPos = pos;

			/// Scale
			Vector2f scale;
			scale = objectToRender->transform.scale() * ((float)cam->pixelsPerUnit() / (float)spritePixelsPerUnit); // Calculate the scale of the sprite using the ratio between
																													// the camera's ppu and the sprite's ppu
			cachedDisplayScale = scale;

			/// Draw Sprite
			pos -= Vector2f(spriteToRender->getTextureRect().width * scale.x, spriteToRender->getTextureRect().height * scale.y) / 2.0f; // Calculate the final position relative to the center of the sprite

			cachedDrawPos = pos;

			spriteToRender->setPosition(pos);
			spriteToRender->setScale(scale);
		}
#pragma endregion
		///

		/// Display
		///
#pragma region Display
		Display::Display()
		{
		}
		Display::Display(Vector2f _resolution, GameWindow* _gameWindow)
			: resolution(_resolution), gameWindow(_gameWindow)
		{
		}
		Display::Display(int resX, int resY, GameWindow* _gameWindow)
			: Display(Vector2f((float)resX, (float)resY), _gameWindow)
		{
		}

		Display::~Display()
		{
			for (auto& ro : renderedObjects)
				delete ro;
		}

#pragma region Setup

		void Display::AddObjectToRender(GameObject* _gameObject, Sprite* _sprite, int _ppu)
		{
			if (ContainsObjectToRender(_gameObject) >= 0) return;

			objectsToRender.push_back(_gameObject);
			renderedObjects.push_back(new RenderedObject(_gameObject, _sprite, _ppu, camera, displayOrigin()));
		}
		void Display::RemoveObjectToRender(GameObject* _gameObject)
		{
			int _i = ContainsObjectToRender(_gameObject);
			if (_i >= 0)
			{
				objectsToRender.erase(objectsToRender.begin() + _i);

				delete renderedObjects[_i];
				renderedObjects.erase(renderedObjects.begin() + _i);
			}
		}

		int Display::ContainsObjectToRender(GameObject* _gameObject)
		{
			for (int i = 0; i < renderedObjects.size(); ++i) {
				if (renderedObjects[i]->objectToRender == _gameObject)
					return i;
			} return -1;
		}
#pragma endregion

		void Display::Render()
		{
			DrawBackground();
			//DrawGrid();

			for (auto& r : renderedObjects)
			{
				r->CalculateDraw();
				Draw(r->spriteToRender);
				//DebugDraw(r);
			}
		}

		void Display::Draw(Sprite* _sprite)
		{
			gameWindow->window->draw(*_sprite);
		}

		void Display::DebugDraw(RenderedObject* _rd)
		{
			RectangleShape point = RectangleShape(Vector2f(4, 4));
			point.setFillColor(RED_COLOR);
			point.setPosition(_rd->cachedDisplayPos);
			gameWindow->window->draw(point);

			RectangleShape rect = RectangleShape(Vector2f(_rd->spriteToRender->getTextureRect().width * _rd->cachedDisplayScale.x,
				_rd->spriteToRender->getTextureRect().height * _rd->cachedDisplayScale.y));
			rect.setOutlineColor(GREEN_COLOR);
			rect.setOutlineThickness(1);
			rect.setFillColor(Color(0, 0, 0, 0));
			rect.setPosition(_rd->cachedDrawPos);
			gameWindow->window->draw(rect);
		}

		void Display::DrawBackground()
		{
			RectangleShape rect = RectangleShape(Vector2f(resolution.x, resolution.y));
			rect.setFillColor(BACKGROUND_COLOR);
			gameWindow->window->draw(rect);
		}

		void Display::DrawGrid()
		{
			int camPPU = camera->pixelsPerUnit();

			const int step = 1000;

			/// Camera Dimensions
			Vector2f camPosition = camera->gameObject->transform.position();
			Vector2f cachedCamOffset = Vector2f((resolution.x / 2) / camPPU, (resolution.y / 2) / camPPU);
			Vector2f minCamPos = camPosition - cachedCamOffset;
			Vector2f maxCamPos = camPosition + cachedCamOffset;

			int lineCount = (int)(floor(maxCamPos.x) - ceil(minCamPos.x));

			int power = Utility::powerOf((float)lineCount / 2, step);
			int base = (int)pow(step, power);
			int currentPPU = camPPU * base;

			int linesX = (int)((Utility::pfloor(maxCamPos.x, base) / base) - (Utility::pceil(minCamPos.x, base) / base));
			cout << linesX << endl;

			float xPos = Utility::pceil(minCamPos.x, base);
			xPos -= camPosition.x;
			xPos *= camPPU;
			xPos += displayOrigin().x;

			for (int x = 0; x <= linesX; ++x)
			{
				float pos = xPos + (float)(x * currentPPU);
				Vertex line[] = { Vertex(Vector2f(pos, 0)), Vertex(Vector2f(pos, resolution.y)) };
				line->color = DETAIL_COLOR;
				//line->color.a = 
				gameWindow->window->draw(line, 2, Lines);
			}

			float yPos = Utility::pceil(minCamPos.y, base);
			yPos -= camPosition.y;
			yPos *= camPPU;
			yPos += displayOrigin().y;

			int linesY = (int)((Utility::pfloor(maxCamPos.y, base) / base) - (Utility::pceil(minCamPos.y, base) / base));

			for (int y = 0; y <= linesY; ++y)
			{
				float pos = yPos + (float)(y * currentPPU);
				Vertex line[] = { Vertex(Vector2f(0, pos)), Vertex(Vector2f(resolution.x, pos)) };
				line->color = DETAIL_COLOR;
				gameWindow->window->draw(line, 2, Lines);
			}

			RectangleShape rect = RectangleShape(Vector2f(15, 15));
			rect.setOutlineColor(RED_COLOR);
			rect.setOutlineThickness(1);
			rect.setFillColor(Color(0, 0, 0, 0));
			rect.setPosition(Vector2f(worldOrigin().x - (rect.getSize().x / 2), worldOrigin().y - (rect.getSize().y / 2)));
			gameWindow->window->draw(rect);
		}
#pragma endregion

		Vector2f Display::ScreenToWorldPosition(Vector2f _screenPosition)
		{
			_screenPosition = Vector2f(_screenPosition.x - gameWindow->window->getSize().x, gameWindow->window->getSize().y - _screenPosition.y);
			_screenPosition /= (float)camera->pixelsPerUnit();
			return _screenPosition;
		}
		Vector2f Display::WorldToScreenPosition(Vector2f _worldPosition)
		{
			_worldPosition *= (float)camera->pixelsPerUnit();
			_worldPosition = Vector2f(displayOrigin().x + _worldPosition.x, displayOrigin().y - _worldPosition.y);
			return _worldPosition;
		}
		///
	}
}
