#include "Display.h"

namespace alpha
{
	namespace core
	{
		/// Displayed Object
		///
#pragma region DisplayedObject
		DisplayedObject::DisplayedObject(GameObject* _gameObject, RenderObject* _renderObject, Camera* _cam, Vector2f _origin)
			: gameObjectToRender(_gameObject), objectToRender(_renderObject), ppu(_renderObject->ppu), cam(_cam), origin(_origin)
		{
			isText = typeid(*_renderObject->drawable) == typeid(Text);
		}

		DisplayedObject::~DisplayedObject()
		{
		}

		void DisplayedObject::CalculateDraw()
		{
			/// Position
			Vector2f pos;
			pos = gameObjectToRender->transform.position() - cam->gameObject->transform.position(); // Calculate the position of the displayed object relative to the camera
			pos *= (float)cam->pixelsPerUnit(); // Convert the position from units to pixels
			pos = Vector2f(origin.x + pos.x, origin.y - pos.y); // Calculate the position relative to the origin (center) of the display (and not the top left corner)

			cachedDisplayPos = pos;

			/// Scale
			Vector2f scale;
			scale = gameObjectToRender->transform.scale() * ((float)cam->pixelsPerUnit() / (float)ppu); // Calculate the scale of the displayed object using the ratio
																										// between the camera's ppu and the displayed object's ppu
			cachedDisplayScale = scale;

			/// Apply
			if (!isText) {
				auto spriteToRender = (SpriteObject*)objectToRender;

				// Calculate the final position relative to the center of the sprite
				pos -= Vector2f(spriteToRender->sprite.getTextureRect().width * scale.x, spriteToRender->sprite.getTextureRect().height * scale.y) / 2.0f;

				cachedDrawPos = pos;

				spriteToRender->sprite.setPosition(pos);
				spriteToRender->sprite.setScale(scale);
			}
			if (isText) {
				auto textToRender = (TextObject*)objectToRender;

				// Calculate the final position relative to the center of the text
				//pos -= Vector2f(textToRender->text.getLocalBounds().width * scale.x, textToRender->text.getLocalBounds().height * scale.y) / 2.0f; 

				pos -= Vector2f(textToRender->text.getLocalBounds().width, textToRender->text.getLocalBounds().height);
				pos += Vector2f(textToRender->text.getLocalBounds().width / 2.0f, 0.0f);
				cachedDrawPos = pos;

				textToRender->text.setPosition(pos);
				//textToRender->SetCharacterSize(ppu * scale.x * 0.2f);
			}
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
			for (auto& d : displayedObjects)
				delete d;
		}

#pragma region Setup

		void Display::AddObjectToRender(GameObject* _gameObject, RenderObject* _renderObject)
		{
			if (ContainsObjectToRender(_renderObject) >= 0) return;

			int key = _renderObject->layer + _renderObject->orderInLayer;
			if (!entries.count(key))
			{
				int cKey = FindClosestKey(key);
				auto d = new DisplayedObject(_gameObject, _renderObject, camera, displayOrigin());

				if (entries.empty()) {
					displayedObjects.push_back(d);
					entries.insert({ key, 1 });
				}
				else {
					displayedObjects.insert(displayedObjects.begin() + entries[cKey], d);
					entries.insert({ key, entries[cKey] + 1 });
				}
			}
			else
			{
				auto d = new DisplayedObject(_gameObject, _renderObject, camera, displayOrigin());
				displayedObjects.insert(displayedObjects.begin() + entries[key], d);
				entries[key]++;
			}
			for (auto& e : entries)
			{
				if (e.second > entries[key])
					e.second++;
			}
		}
		int Display::FindClosestKey(int _key)
		{
			int cKey = 0;
			for (auto& e : entries) {
				if (e.first > _key) continue;
				if (e.first > cKey)
					cKey = e.first;
			}
			return cKey;
		}

		void Display::RemoveObjectToRender(RenderObject* _renderObject)
		{
			int _i = ContainsObjectToRender(_renderObject);
			if (_i >= 0)
			{
				delete displayedObjects[_i];
				displayedObjects.erase(displayedObjects.begin() + _i);
			}
		}

		int Display::ContainsObjectToRender(RenderObject* _renderObject)
		{
			for (int i = 0; i < displayedObjects.size(); ++i) {
				if (displayedObjects[i]->objectToRender == _renderObject)
					return i;
			} return -1;
		}
#pragma endregion

		void Display::Render()
		{
			DrawBackground();
			//DrawGrid();

			for (auto& d : displayedObjects) {
				if (d->objectToRender->render == false) continue;
				d->CalculateDraw();
				Draw(d->objectToRender->drawable, d);
				//DebugDraw(r);
			}
		}

		void Display::Draw(Drawable* _drawable, DisplayedObject* _d)
		{
			gameWindow->window->draw(*_drawable);
		}

		void Display::DebugDraw(DisplayedObject* _d)
		{
			if (_d->isText) return;

			RectangleShape point = RectangleShape(Vector2f(4, 4));
			point.setFillColor(RED_COLOR);
			point.setPosition(_d->cachedDisplayPos);
			gameWindow->window->draw(point);

			auto spriteToRender = (SpriteObject*)_d->objectToRender;

			RectangleShape rect = RectangleShape(Vector2f(spriteToRender->sprite.getTextureRect().width * _d->cachedDisplayScale.x,
				spriteToRender->sprite.getTextureRect().height * _d->cachedDisplayScale.y));
			rect.setOutlineColor(GREEN_COLOR);
			rect.setOutlineThickness(1);
			rect.setFillColor(Color(0, 0, 0, 0));
			rect.setPosition(_d->cachedDrawPos);
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
			_screenPosition = Vector2f(_screenPosition.x - displayOrigin().x, displayOrigin().y - _screenPosition.y);
			_screenPosition /= (float)camera->pixelsPerUnit();
			_screenPosition += camera->gameObject->transform.position();
			return _screenPosition;
		}
		Vector2f Display::WorldToScreenPosition(Vector2f _worldPosition)
		{
			_worldPosition -= camera->gameObject->transform.position();
			_worldPosition *= (float)camera->pixelsPerUnit();
			_worldPosition = Vector2f(displayOrigin().x + _worldPosition.x, displayOrigin().y - _worldPosition.y);
			return _worldPosition;
		}

		Vector2f Display::MousePositionToWorld()
		{
			Vector2f mousePosition = (Vector2f)Mouse::getPosition(*gameWindow->window);
			return ScreenToWorldPosition(mousePosition);
		}
	}
}
