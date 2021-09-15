#include "ConstructionInput.h"

namespace alpha
{
	namespace game
	{
		ConstructionInput::ConstructionInput(Display& _display, Grid* _grid)
			: display(_display), grid(_grid), offsetFromMouse(Vector2f(0.4f, 0.4f))
		{
		}
		ConstructionInput::ConstructionInput(const ConstructionInput& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject), display(that.display), grid(that.grid), offsetFromMouse(that.offsetFromMouse)
		{
		}

		ConstructionInput* ConstructionInput::Clone(GameObject* _gameObject)
		{
			return new ConstructionInput(*this, _gameObject);
		}

		void ConstructionInput::Init()
		{
			hoveredSquarePrefab = AssetManager::LoadAsset("Hovered Square");

			archBuildings = vector<pair<BuildingType, ArchBuilding>>
			{
				{ BuildingType::DroneBay, DRONE_BAY_BUILDING },
				{ BuildingType::Pharmacy, PHARMACY_BUILDING },
				{ BuildingType::Prefabs, PREFABS_BUILDING },
				{ BuildingType::Shed, SHED_BUILDING },
				{ BuildingType::Storage, STORAGE_BUILDING },
				{ BuildingType::Farm, FARM_BUILDING },
				{ BuildingType::HuntCamp, HUNT_CAMP_BUILDING },
				{ BuildingType::Cookery, COOKERY_BUILDING },
				{ BuildingType::OxygenGatherer, OXYGEN_GATHERER_BUILDING },
				{ BuildingType::OxygenExcavator, OXYGEN_EXCAVATOR_BUILDING },
				{ BuildingType::WaterExtractor, WATER_EXTRACTOR_BUILDING },
				{ BuildingType::WaterPurifier, WATER_PURIFIER_BUILDING }
			};

			buildingPrefab = AssetManager::LoadAsset("Building");
		}

		void ConstructionInput::Start()
		{
			buildingPreview = AssetManager::InstantiateAsset(GameObject("Preview Building"));
			auto previewSr = buildingPreview->AddComponent(new SpriteRenderer(buildingPreview, AssetManager::currentSceneDisplay, SelectedBuildingSprite(), 16));
			previewSr->SetLayer(Layers::DETAILS_LAYER);
			Color transparent = Color(255, 255, 255, 204);
			buildingPreview->GetComponent<SpriteRenderer>()->GetSprite()->setColor(transparent);

			hoveredSquare = AssetManager::InstantiateAsset(*hoveredSquarePrefab);

			buildingIcon = AssetManager::InstantiateAsset(GameObject("Icon Building"));
			auto iconSr = buildingIcon->AddComponent(new SpriteRenderer(buildingIcon, AssetManager::currentSceneDisplay, SelectedBuildingSprite(), 16));
			iconSr->SetLayer(Layers::UI_LAYER);
			buildingIcon->transform.localScale /= 2.0f;
		}
		void ConstructionInput::Update(float _elapsedTime)
		{
			scrollThroughBuildings = Keyboard::isKeyPressed(Keyboard::LShift);

			currentMousePosition = display.MousePositionToWorld();

			Vector2f iconPos = currentMousePosition + offsetFromMouse;
			buildingIcon->transform.localPosition = iconPos;

			Vector2f tileMousePos = Vector2f(round(currentMousePosition.x), round(currentMousePosition.y));
			buildingPreview->transform.localPosition = tileMousePos;
			hoveredSquare->transform.localPosition = tileMousePos;

			auto hoveredTile = grid->GetTile((int)tileMousePos.x, (int)tileMousePos.y);

			if (hoveredTile != currentHoveredTile || selectedBuildingChanged)
			{
				selectedBuildingChanged = false;

				if (currentHoveredTile != nullptr && currentHoveredTile->tile->biomeType != BiomeType::None)
				{
					///
					/// Disable all previous displays relative to the current hovered tile

					for (auto& ri : currentHoveredTile->resourceIconsSpriteRenderers)
						ri.second->SetActive(false);
					currentHoveredTile->excavationIcon->SetActive(false);
					currentHoveredTile->areaSquare->SetActive(false);
					currentHoveredTile->invalidTile->SetActive(false);

					for (auto& t : currentPotentialExploitedTiles) {
						for (auto& ri : t->resourceIconsSpriteRenderers)
							ri.second->SetActive(false);
						t->areaSquare->SetActive(false);
					}
					currentPotentialExploitedTiles.clear();
						///
				}

				///
				/// Set the current tile as the new hovered tile

				currentHoveredTile = hoveredTile;

				if (currentHoveredTile == nullptr || currentHoveredTile->tile->biomeType == BiomeType::None) return;

				auto currentTile = currentHoveredTile->tile;
				auto currentBiome = currentTile->getBiome();

				currentBuildIsValid = true;
					///

				///
				/// Display potential exploited tiles, and potential structures destruction, and if the tile is invalid or not, for the new hovered tile

				if (!currentBiome->allowBuild) {
					currentHoveredTile->invalidTile->SetActive(true);
					currentBuildIsValid = false;
					return;
				}

				if (currentTile->hasBuilding()) {
					currentHoveredTile->invalidTile->SetActive(true);
					currentBuildIsValid = false;
					return;
				}

				auto selectedArchBuilding = archBuildings[selected].second;

				for (auto& cc : selectedArchBuilding.constructionCosts) {
					// Check for global storage to check if resources match the cost
				}

				if (selectedArchBuilding.requiredBiome != BiomeType::None)
				{
					auto result = SearchTileAndSurroundings(currentHoveredTile, &selectedArchBuilding, selectedArchBuilding.areaOfEffect, true);
					if (result <= 0) {
						currentHoveredTile->invalidTile->SetActive(true);
						currentBuildIsValid = false;
						return;
					}
				}

				if (currentBiome->HasStructures()) {
					if (currentBiome->structures.count(StructureType::ShipParts)) {
						currentHoveredTile->excavationIcon->SetActive(true);
						currentBuildExcavatesStructures = true;
					}
					else if (currentBiome->structures.count(StructureType::Trees)) {
						if (selectedArchBuilding.treesStatus == ebStatus::Destroy) {
							currentHoveredTile->excavationIcon->SetActive(true);
							currentBuildExcavatesStructures = true;
						}
					}
				}
					///
			}
		}
		int ConstructionInput::SearchTileAndSurroundings(TileObject* _tileObject, ArchBuilding* _archBuilding, int _depth, bool _first)
		{
			auto status = SetupTileAsExploited(_tileObject, _archBuilding);

			if (_depth <= 0) return status;

			if (!_first && status <= 0) return status;

			for (int i = 0; i < 4; i++)
			{
				TileObject* adjacentTile = nullptr;

				if (i == 0)
					adjacentTile = grid->GetTile(_tileObject->tile->x - 1, _tileObject->tile->y);
				if (i == 1)
					adjacentTile = grid->GetTile(_tileObject->tile->x + 1, _tileObject->tile->y);
				if (i == 2)
					adjacentTile = grid->GetTile(_tileObject->tile->x, _tileObject->tile->y - 1);
				if (i == 3)
					adjacentTile = grid->GetTile(_tileObject->tile->x, _tileObject->tile->y + 1);

				if (adjacentTile != nullptr && adjacentTile->tile->biomeType != BiomeType::None)
					status += SearchTileAndSurroundings(adjacentTile, _archBuilding, _depth - 1, false);
			}
			return status;
		}
		int ConstructionInput::SetupTileAsExploited(TileObject* _tileObject, ArchBuilding* _selectedArchBuilding)
		{
			auto tile = _tileObject->tile;
			auto biome = tile->getBiome();

			if (biome->biomeType == _selectedArchBuilding->requiredBiome)
			{
				if (tile->hasBuilding()) return 0;

				int resource = _selectedArchBuilding->requiredResource;
				if (biome->exploitationResources[resource].GetQuantity() > 0)
				{
					_tileObject->resourceIconsSpriteRenderers[resource]->SetActive(true);
					_tileObject->areaSquare->SetActive(true);
				}

				currentPotentialExploitedTiles.push_back(_tileObject);

				return 1;
			}
			return 0;
		}

		void ConstructionInput::EventUpdate(Event& _event, float _elapsedTime)
		{
			if (scrollThroughBuildings) {
				if (_event.type == Event::MouseWheelScrolled)
				{
					float ticks = _event.mouseWheelScroll.delta;

					selected += (int)ticks;
					if (selected < 0) selected = 0;
					if (selected >= archBuildings.size()) selected = (int)archBuildings.size() - 1;
					
					buildingIcon->GetComponent<SpriteRenderer>()->SetSprite(SelectedBuildingSprite());
					buildingPreview->GetComponent<SpriteRenderer>()->SetSprite(SelectedBuildingSprite());

					selectedBuildingChanged = true;
				}
			}

			if (_event.type == Event::MouseButtonPressed) {
				if (_event.mouseButton.button == sf::Mouse::Left) {

					if (currentHoveredTile == nullptr || currentHoveredTile->tile->biomeType == BiomeType::None) return;

					if (currentBuildIsValid)
					{
						// Transfer the list of TileObjects to Tiles
						auto exploitedTiles = vector<Tile*>();
						for (auto& to : currentPotentialExploitedTiles)
							exploitedTiles.push_back(to->tile);

						// Construct Building
						auto bgo = AssetManager::InstantiateAsset(*buildingPrefab, nullptr, buildingPreview->transform.localPosition);
						auto bo = bgo->GetComponent<BuildingObject>();

						bo->building = Construction::ConstructBuilding(currentHoveredTile->tile, archBuildings[selected].first, exploitedTiles);

						bgo->GetComponent<SpriteRenderer>()->SetSprite(Utility::spritePath(bo->building->archBuilding.sprite));

						// Destroy what needs to
						auto currentTile = currentHoveredTile->tile;
						auto currentBiome = currentTile->getBiome();

						if (bo->building->archBuilding.exploitedBiomeResourcesStatus == ebStatus::Destroy) {
							currentBiome->DestroyResources();
						}
						if (currentBuildExcavatesStructures)
						{
							if (currentTile->biomeType == BiomeType::Forest) {
								if (bo->building->archBuilding.treesStatus == ebStatus::Destroy) {
									currentBiome->RemoveStructure(StructureType::Trees);
								}
							}
							currentBiome->RemoveStructure(StructureType::ShipParts);
						}
					}
				}
			}
		}
	}
}
