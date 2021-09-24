#pragma once

#ifndef CONSTRUCTION_INPUT_H
#define CONSTRUCTION_INPUT_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Display.h"
#include "Construction.h"
#include "BuildingObject.h"
#include "Grid.h"

namespace alpha
{
	using namespace core;

	namespace game
	{
		class ConstructionInput : public ScriptBehaviour
		{
		public:

			ConstructionInput(Display& _display, Grid* _grid);
			ConstructionInput(const ConstructionInput& that, GameObject* _gameObject);

			ConstructionInput* Clone(GameObject* _gameObject) override;

			void Init() override;

			void Start() override;
			void Update(float _elapsedTime) override;
			void EventUpdate(Event& _event, float _elapsedTime) override;

			int SearchTileAndSurroundings(TileObject* _tileObject, ArchBuilding* _archBuilding, int _depth, bool _first);
			int SetupTileAsExploited(TileObject* _tileObject, ArchBuilding* _selectedArchBuilding);

		private:

			Display& display;

			Grid* grid;

			vector<pair<BuildingType, ArchBuilding>> archBuildings;

			GameObject* buildingPrefab = nullptr;

			GameObject* buildingIcon = nullptr;
			Vector2f offsetFromMouse;
			GameObject* buildingPreview = nullptr;

			GameObject* invalidTile = nullptr;
			SpriteRenderer* invalidTileSr = nullptr;

			GameObject* hoveredSquarePrefab;
			GameObject* hoveredSquare = nullptr;

			int selected = 0;
			bool scrollThroughBuildings = false;
			bool selectedBuildingChanged = false;

			Vector2f currentMousePosition;

			TileObject* currentHoveredTile = nullptr;
			vector<TileObject*> currentPotentialExploitedTiles = vector<TileObject*>();

			bool currentBuildIsValid;
			bool currentBuildExcavatesStructures;
		};
	}
}

#endif // !CONSTRUCTION_INPUT_H
