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
			/*for (auto& d : _renderObject->drawables) {
				if (typeid(*d) == typeid(Text)) {
					isText = true;
					break;
				}
			}*/

			if (typeid(*_renderObject) == typeid(TextObject)) {
				isText = true;
			}

			auto tr = dynamic_cast<UITransform*>(_gameObject->transform);
			if (tr) {
				if (tr->renderMode == RenderSpace::ScreenSpace)
					isUI = true;
			}

			// What's the difference between the two ?
			// Which of them works, if not both ?
			// Has polymorphism made it work ?
			// Is the overriden Create method, called through the parent object in the constructor, indeed overriden or is it the base method called ?
			// How can you make it polymorphic, without too much overhead ?
			// How can you reduce the amount of constructors safely and make a quicker and more straightforward architecture ?
			// How does typeid actually works ?
			// Why can't you implicitly call the parent's parent constructor from a constructor, nor set the parent's or parent's parent's parameters ?

			/*if (typeid(*_renderObject) == typeid(SpriteObject)) {

			}
			if (typeid(_renderObject) == typeid(SpriteObject*)) {

			}*/
		}

		DisplayedObject::~DisplayedObject()
		{
		}

		void DisplayedObject::CalculateDraw()
		{
			/// Position
			Vector2f pos;
			pos = gameObjectToRender->transform->position() - cam->gameObject->transform->position(); // Calculate the position of the displayed object relative to the camera
			pos *= (float)cam->pixelsPerUnit(); // Convert the position from units to pixels
			pos = Vector2f(origin.x + pos.x, origin.y - pos.y); // Calculate the position relative to the origin (center) of the display (and not the top left corner)

			cachedDisplayPos = pos;

			/// Scale
			Vector2f scale;
			scale = gameObjectToRender->transform->scale() * ((float)cam->pixelsPerUnit() / (float)ppu); // Calculate the scale of the displayed object using the ratio
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
		void DisplayedObject::CalculateUIDraw()
		{
			auto uiSpriteToRender = (UISpriteObject*)objectToRender;

			Vector2f pos;
			pos = gameObjectToRender->transform->position();
			pos = Vector2f(origin.x + pos.x, origin.y - pos.y);

			Vector2f scale;
			scale = gameObjectToRender->transform->scale();

			pos -= Vector2f(scale.x, scale.y) / 2.0f;

			uiSpriteToRender->shape.setSize(scale);
			uiSpriteToRender->shape.setPosition(pos);
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
			for (auto& dpair : displayedObjects) {
				for (auto& d : dpair.second)
					delete d;
			}
		}

#pragma region Setup

		void Display::AddObjectToRender(GameObject* _gameObject, RenderObject* _renderObject)
		{
			if (ContainsObjectToRender(_renderObject).first >= 0) return;

			int key = _renderObject->layer + _renderObject->orderInLayer;

			if (!displayedObjects.count(key)) {
				int k = FindKeyPosition(key);
				entries.insert(entries.begin() + k, key);
				displayedObjects.insert({ key, vector<DisplayedObject*>() });
			}
			auto d = new DisplayedObject(_gameObject, _renderObject, camera, displayOrigin());
			displayedObjects[key].push_back(d);
		}
		int Display::FindKeyPosition(int _newKey)
		{
			for (int i = 0; i < entries.size(); i++)
			{
				if (entries[i] > _newKey) {
					return i;
				}
			}
		}

		void Display::RemoveObjectToRender(RenderObject* _renderObject)
		{
			pair<int, int> p = ContainsObjectToRender(_renderObject);
			auto key = p.first;
			auto index = p.second;
			if (key >= 0)
			{
				delete displayedObjects[key][index];
				displayedObjects[key].erase(displayedObjects[key].begin() + index);
			}
		}

		pair<int, int> Display::ContainsObjectToRender(RenderObject* _renderObject)
		{
			for (auto& dpair : displayedObjects) {
				for (int i = 0; i < dpair.second.size(); ++i) {
					if (dpair.second[i]->objectToRender == _renderObject)
						return { dpair.first, i };
				}
			} return { -1, -1 };
		}
#pragma endregion

		void Display::Render()
		{
			DrawBackground();
			//DrawGrid();

			for (int i = 0; i < entries.size(); i++) {
				for (auto& d : displayedObjects[entries[i]])
				{
					if (d->objectToRender->render == false)
						continue;

					if (d->isUI)
						d->CalculateUIDraw();
					else
						d->CalculateDraw();

					for (auto& dw : d->objectToRender->drawables)
						Draw(dw, d);
				}
			}

			//RectangleShape rect = RectangleShape(Vector2f(1, 1));
			//rect.setFillColor(Color::Blue);
			//rect.setSize(Vector2f(400, 100));
			//rect.setOutlineThickness(-1.0f);
			//gameWindow->window->draw(rect);
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
			rect.setFillColor(backgroundColor);
			gameWindow->window->draw(rect);
		}

		void Display::DrawGrid()
		{
			int camPPU = camera->pixelsPerUnit();

			const int step = 1000;

			/// Camera Dimensions
			Vector2f camPosition = camera->gameObject->transform->position();
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
			_screenPosition += camera->gameObject->transform->position();
			return _screenPosition;
		}
		Vector2f Display::WorldToScreenPosition(Vector2f _worldPosition)
		{
			_worldPosition -= camera->gameObject->transform->position();
			_worldPosition *= (float)camera->pixelsPerUnit();
			_worldPosition = Vector2f(displayOrigin().x + _worldPosition.x, displayOrigin().y - _worldPosition.y);
			return _worldPosition;
		}

		Vector2f Display::MousePositionToWorld()
		{
			Vector2f mousePosition = (Vector2f)Mouse::getPosition(*gameWindow->window);
			return ScreenToWorldPosition(mousePosition);
		}

		void Display::SetBackgroundColor(Color _color) { backgroundColor = _color; }

		Color Display::BackgroundColor() { return backgroundColor; }
	}
}
