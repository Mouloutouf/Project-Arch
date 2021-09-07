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

		private:

			Grid* grid;

			Display& display;

			GameObject* buildingPrefab = nullptr;

			vector<pair<BuildingType, ArchBuilding>> archBuildings;

			Vector2f offsetFromMouse;
			GameObject* buildingSelectedObject = nullptr;
			GameObject* buildingPreviewObject = nullptr;

			int selected = 0;
			bool scrollThroughBuildings = false;

			Vector2f currentMousePosition;

			string SelectedBuildingSprite() { return ASSETS_FOLDER + archBuildings[selected].second.sprite + ".png"; }
			TileObject* hoveredTile = nullptr;

			vector<Tile*> currentValidTiles = vector<Tile*>();
		};
	}
}

#endif // !CONSTRUCTION_INPUT_H
