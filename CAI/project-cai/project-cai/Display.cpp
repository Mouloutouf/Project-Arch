#include "Display.h"

namespace alpha
{
	namespace core
	{
		/// Rendered Object
		///
#pragma region RenderedObject
		RenderedObject::RenderedObject()
		{
		}
		RenderedObject::RenderedObject(SpriteRenderer* _sr, Camera* _cam, Vector2f _origin)
			: spriteRenderer(_sr), cam(_cam), origin(_origin)
		{
			sprite = spriteRenderer->GetSprite();
		}

		RenderedObject::~RenderedObject()
		{
		}

		void RenderedObject::CalculateDraw()
		{
			/// Position
			Vector2f pos;
			pos = spriteRenderer->gameObject->transform.position() - cam->gameObject->transform.position(); // Calculate the position of the sprite relative to the camera
			pos *= (float)cam->ppu(); // Convert the position from units to pixels
			pos = Vector2f(origin.x + pos.x, origin.y - pos.y); // Calculate the position relative to the origin of the display (and not the top left corner)

			cachedDisplayPos = pos;

			/// Scale
			Vector2f scale;
			scale = spriteRenderer->gameObject->transform.scale() * ((float)cam->ppu() / (float)spriteRenderer->pixelsPerUnit); // Calculate the scale of the sprite using the ratio between
																																// the camera's ppu and the sprite's ppu
			cachedDisplayScale = scale;

			/// Draw Sprite
			pos -= Vector2f(sprite->getTextureRect().width * scale.x, sprite->getTextureRect().height * scale.y) / 2.0f; // Calculate the final position relative to the center of the sprite

			cachedDrawPos = pos;

			sprite->setPosition(pos);
			sprite->setScale(scale);
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
		}

#pragma region Setup
		void Display::Setup(vector<SpriteRenderer*> _srs, Camera* _camera)
		{
			cameraObject = _camera;

			for (auto& sr : _srs)
			{
				AddObjectToRender(sr);
			}
		}

		void Display::AddObjectToRender(SpriteRenderer* _sr)
		{
			if (ContainsObjectToRender(_sr) >= 0) return;

			spriteObjects.push_back(_sr);

			RenderedObject _r = RenderedObject(_sr, cameraObject, displayOrigin());
			renderedObjects.push_back(_r);
		}
		void Display::RemoveObjectToRender(SpriteRenderer* _sr)
		{
			int _i = ContainsObjectToRender(_sr);
			if (_i >= 0)
			{
				spriteObjects.erase(spriteObjects.begin() + _i);

				renderedObjects.erase(renderedObjects.begin() + _i);
			}
		}

		int Display::ContainsObjectToRender(SpriteRenderer* _sr)
		{
			for (int i = 0; i < renderedObjects.size(); ++i) {
				if (renderedObjects[i].spriteRenderer == _sr)
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
				r.CalculateDraw();
				Draw(r.sprite);
				DebugDraw(&r);
			}
		}

		void Display::Draw(Sprite* _sprite)
		{
			gameWindow->window->draw(*_sprite);
		}

		void Display::DebugDraw(RenderedObject* _rd)
		{
			RectangleShape point = RectangleShape(Vector2f(4, 4));
			point.setFillColor(redColor);
			point.setPosition(_rd->cachedDisplayPos);
			gameWindow->window->draw(point);

			RectangleShape rect = RectangleShape(Vector2f(_rd->sprite->getTextureRect().width * _rd->cachedDisplayScale.x,
				_rd->sprite->getTextureRect().height * _rd->cachedDisplayScale.y));
			rect.setOutlineColor(greenColor);
			rect.setOutlineThickness(1);
			rect.setFillColor(Color(0, 0, 0, 0));
			rect.setPosition(_rd->cachedDrawPos);
			gameWindow->window->draw(rect);
		}

		void Display::DrawBackground()
		{
			RectangleShape rect = RectangleShape(Vector2f(resolution.x, resolution.y));
			rect.setFillColor(backgroundColor);
			gameWindow->window->draw(rect);
		}

		void Display::DrawGrid()
		{
			int camPPU = cameraObject->ppu();

			const int step = 10;

			/// Camera Dimensions
			Vector2f camPosition = cameraObject->gameObject->transform.position();
			Vector2f cachedCamOffset = Vector2f((resolution.x / 2) / camPPU, (resolution.y / 2) / camPPU);
			Vector2f minCamPos = camPosition - cachedCamOffset;
			Vector2f maxCamPos = camPosition + cachedCamOffset;

			int lineCount = (int)(floor(maxCamPos.x) - ceil(minCamPos.x));

			int power = powerOf((float)lineCount / 2, step);
			int base = (int)pow(step, power);
			int currentPPU = camPPU * base;

			int linesX = (int)((pfloor(maxCamPos.x, base) / base) - (pceil(minCamPos.x, base) / base));
			cout << linesX << endl;

			float xPos = pceil(minCamPos.x, base);
			xPos -= camPosition.x;
			xPos *= camPPU;
			xPos += displayOrigin().x;

			for (int x = 0; x <= linesX; ++x)
			{
				float pos = xPos + (float)(x * currentPPU);
				Vertex line[] = { Vertex(Vector2f(pos, 0)), Vertex(Vector2f(pos, resolution.y)) };
				line->color = detailColor;
				//line->color.a = 
				gameWindow->window->draw(line, 2, Lines);
			}

			float yPos = pceil(minCamPos.y, base);
			yPos -= camPosition.y;
			yPos *= camPPU;
			yPos += displayOrigin().y;

			int linesY = (int)((pfloor(maxCamPos.y, base) / base) - (pceil(minCamPos.y, base) / base));

			for (int y = 0; y <= linesY; ++y)
			{
				float pos = yPos + (float)(y * currentPPU);
				Vertex line[] = { Vertex(Vector2f(0, pos)), Vertex(Vector2f(resolution.x, pos)) };
				line->color = detailColor;
				gameWindow->window->draw(line, 2, Lines);
			}

			RectangleShape rect = RectangleShape(Vector2f(15, 15));
			rect.setOutlineColor(redColor);
			rect.setOutlineThickness(1);
			rect.setFillColor(Color(0, 0, 0, 0));
			rect.setPosition(Vector2f(worldOrigin().x - (rect.getSize().x / 2), worldOrigin().y - (rect.getSize().y / 2)));
			gameWindow->window->draw(rect);
		}
#pragma endregion
		///
	}
}
