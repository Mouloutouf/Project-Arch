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

RenderedObject::RenderedObject(SpriteRenderer* _sr, Camera* _cam, Vector2i _origin)
	: sr(_sr), cam(_cam), origin(_origin)
{
	sprite = sr->GetSprite();
}

RenderedObject::~RenderedObject()
{
}

void RenderedObject::Draw()
{
	/// Position

	Vector2f spritePos = sr->gameObject->transform.position();
	Vector2f cameraPos = cam->gameObject->transform.position();
	Vector2f worldPos = spritePos - cameraPos;

	int cameraPPU = cam->ppu();
	Vector2i pixelWorldPos = (Vector2i)(worldPos * (float)cameraPPU);

	Vector2i displayPos = Vector2i(origin.x + pixelWorldPos.x, origin.y - pixelWorldPos.y);

	/// Scale

	Vector2f spriteScale = sr->gameObject->transform.scale();
	int spritePPU = sr->ppu;
	Vector2f displayScale = spriteScale * (float)(cameraPPU / spritePPU);

	/// Draw Sprite

	sprite->setPosition((Vector2f)displayPos);
	sprite->setScale(displayScale);
}
#pragma endregion


#pragma region Display
Display::Display()
{
}
Display::Display(Vector2i _resolution)
	: resolution(_resolution)
{
}
Display::Display(int resX, int resY)
{
	resolution = Vector2i(resX, resY);
}

Display::~Display()
{
}

void Display::Setup(vector<SpriteRenderer*> _spriteObjects, Camera* _cameraObject)
{
	spriteObjects = _spriteObjects;
	cameraObject = _cameraObject;
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
	for (auto r : renderedObjects)
	{
		r.Draw();
	}
}

int Display::ContainsSpriteObject(SpriteRenderer* _spriteObject)
{
	for (int i = 0; i < spriteObjects.size(); i++)
	{
		if (spriteObjects[i] == _spriteObject)
		{
			return i;
		}
	}
	return -1;
}
#pragma endregion