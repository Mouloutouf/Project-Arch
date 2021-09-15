#pragma once

#ifndef TILE_OBJECT_H
#define TILE_OBJECT_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Tile.h"

namespace alpha
{
	namespace game
	{
		class TileObject : public ScriptBehaviour
		{
		public:
			TileObject();
			TileObject(Tile* _tile, SpriteRenderer* _spriteRenderer);
			TileObject(const TileObject& that, GameObject* _gameObject);
			~TileObject();

			TileObject* Clone(GameObject* _gameObject) override;

			void Init() override;
			void Start() override;
			void Update(float _elapsedTime) override;

			void SetupTile(int x, int y);

			Tile* tile;
			Biome* biome;

			SpriteRenderer* biomeDisplay;

			GameObject* tileDisplayPrefab;
			GameObject* tileDisplay;

			SpriteRenderer* areaSquare;
			map<__ResourceType, SpriteRenderer*> resourceIconsSpriteRenderers;
			SpriteRenderer* excavationIcon;
			SpriteRenderer* invalidTile;
		};
	}
}

#endif // !TILE_OBJECT_H
