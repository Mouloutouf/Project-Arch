#include "Display.h"

#pragma region RenderedObject
RenderedObject::RenderedObject()
{
}
//RenderedObject::RenderedObject(Sprite* _sprite, Vector2f _sPos, Vector2f _cPos, int _cppu, Vector2i _wPos, Vector2f _sScale, int _sppu)
//	: sprite(_sprite)
//{
//	rwPos = _sPos - _cPos;
//	rdPos = (Vector2i)(rwPos * (float)_cppu);
//	dPos = Vector2i(_wPos.x + rdPos.x, _wPos.y - rdPos.y);
//
//	dScale = _sScale * (float)(_cppu / _sppu);
//}
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

	Vector2f spriteRendererPos = spriteRenderer->gameObject->transform.position();
	Vector2f cameraPos = cam->gameObject->transform.position();
	Vector2f worldPos = spriteRendererPos - cameraPos;

	int cameraPPU = cam->ppu();
	Vector2f pixelWorldPos = worldPos * (float)cameraPPU;

	Vector2f displayPos = Vector2f(origin.x + pixelWorldPos.x, origin.y - pixelWorldPos.y);

	cachedDisplayPos = displayPos;

	/// Scale

	Vector2f spriteScale = spriteRenderer->gameObject->transform.scale();
	int spritePPU = spriteRenderer->pixelsPerUnit;
	Vector2f displayScale = spriteScale * ((float)cameraPPU / (float)spritePPU);

	cachedDisplayScale = displayScale;

	/// Draw Sprite

	Vector2f displayRect = Vector2f(sprite->getTextureRect().width * displayScale.x, sprite->getTextureRect().height * displayScale.y) / 2.0f;
	displayPos -= displayRect;

	cachedDrawPos = displayPos;

	sprite->setPosition(displayPos);
	sprite->setScale(displayScale);
}
#pragma endregion


#pragma region Display
Display::Display()
{
}
Display::Display(Vector2f _resolution, GameWindow* _gameWindow)
	: resolution(_resolution), gameWindow(_gameWindow)
{
}
Display::Display(int resX, int resY, GameWindow* _gameWindow)
	: Display(Vector2f(resX, resY), _gameWindow)
{
}

Display::~Display()
{
}

void Display::Setup(vector<SpriteRenderer*> _spriteObjects, Camera* _cameraObject)
{
	cameraObject = _cameraObject;

	for (auto& sr : _spriteObjects)
	{
		AddObjectToRender(sr);
	}
}

void Display::AddObjectToRender(SpriteRenderer* _spriteObject)
{
	if (ContainsSpriteObject(_spriteObject) >= 0) return;

	spriteObjects.push_back(_spriteObject);

	RenderedObject _r = RenderedObject(_spriteObject, cameraObject, origin());
	renderedObjects.push_back(_r);
}
void Display::RemoveObjectToRender(SpriteRenderer* _spriteObject)
{
	int _i = ContainsSpriteObject(_spriteObject);
	if (_i >= 0)
	{
		spriteObjects.erase(spriteObjects.begin() + _i);

		renderedObjects.erase(renderedObjects.begin() + _i);
	}
}

void Display::Render()
{
	DrawGrid();

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
	point.setFillColor(Color(255, 0, 0));
	point.setPosition(_rd->cachedDisplayPos);
	gameWindow->window->draw(point);

	RectangleShape rect = RectangleShape(Vector2f(_rd->sprite->getTextureRect().width * _rd->cachedDisplayScale.x, 
		_rd->sprite->getTextureRect().height * _rd->cachedDisplayScale.y));
	rect.setOutlineColor(Color(0, 255, 0));
	rect.setOutlineThickness(1);
	rect.setFillColor(Color(0, 0, 0, 0));
	rect.setPosition(_rd->cachedDrawPos);
	gameWindow->window->draw(rect);
}

void Display::DrawGrid()
{
	int camPPU = cameraObject->ppu();

	Vector2f camPosition = cameraObject->gameObject->transform.position();
	Vector2f cachedCamOffset = Vector2f((resolution.x / 2) / camPPU, (resolution.y / 2) / camPPU);
	Vector2f minCamPos = camPosition - cachedCamOffset;
	Vector2f maxCamPos = camPosition + cachedCamOffset;

	for (int x = ceil(minCamPos.x); x <= floor(maxCamPos.x); x++)
	{
		float xWorldPos = x - camPosition.x;
		float xPos = xWorldPos * camPPU;

		float xDisplayPos = origin().x + xPos;

		Vertex line[] = { Vertex(Vector2f(xDisplayPos, 0)), Vertex(Vector2f(xDisplayPos, resolution.y)) };
		gameWindow->window->draw(line, 2, Lines);
	}
	for (int y = ceil(minCamPos.y); y <= floor(maxCamPos.y); y++)
	{
		float yWorldPos = y - camPosition.y;
		float yPos = yWorldPos * camPPU;

		float yDisplayPos = origin().y - yPos;

		Vertex line[] = { Vertex(Vector2f(0, yDisplayPos)), Vertex(Vector2f(resolution.x, yDisplayPos)) };
		gameWindow->window->draw(line, 2, Lines);
	}

	RectangleShape rect = RectangleShape(Vector2f(15, 15));
	rect.setOutlineColor(Color(255, 0, 0));
	rect.setOutlineThickness(1);
	rect.setFillColor(Color(0, 0, 0, 0));
	//rect.setPosition(origin());
	rect.setPosition(Vector2f(origin().x - (rect.getSize().x / 2), origin().y - (rect.getSize().y / 2)));
	gameWindow->window->draw(rect);
}

int Display::ContainsSpriteObject(SpriteRenderer* _spriteObject)
{
	for (int i = 0; i < renderedObjects.size(); i++)
	{
		if (renderedObjects[i].spriteRenderer == _spriteObject)
		{
			return i;
		}
	}
	return -1;
}
#pragma endregion