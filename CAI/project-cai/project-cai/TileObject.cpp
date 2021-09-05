#include "TileObject.h"

namespace alpha
{
	namespace game
	{
		TileObject::TileObject()
			: tile(new Tile())
		{
			spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
		}
		TileObject::TileObject(Tile* _tile, SpriteRenderer* _spriteRenderer)
			: tile(_tile), spriteRenderer(_spriteRenderer)
		{
		}

		TileObject::TileObject(const TileObject& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject), tile(that.tile), spriteRenderer(that.spriteRenderer)
		{
		}

		TileObject::~TileObject()
		{
			delete tile;
		}

		TileObject* TileObject::Clone(GameObject* _gameObject)
		{
			return new TileObject(*this, _gameObject);
		}

		void TileObject::Init()
		{
		}

		void TileObject::Start()
		{
		}
		void TileObject::Update(float _elapsedTime)
		{
			if (tile->hasBuilding()) {
				tile->getBuilding()->Process(_elapsedTime);
			}
		}
	}
}