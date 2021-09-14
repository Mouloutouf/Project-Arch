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

			if (hoveredTile != currentHoveredTile)
			{
				// Disable all previous displays relative to the current hovered tile

				currentHoveredTile = hoveredTile; // Set the current tile as the new hovered tile

				// Display available and unavailable tiles, potential exploited tiles, and potential structures destruction, for the new hovered tile
			}
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
				}
			}

			if (_event.type == Event::MouseButtonPressed) {
				if (_event.mouseButton.button == sf::Mouse::Left) {

					if (currentHoveredTile == nullptr) return;
					//Temp
					auto bgo = AssetManager::InstantiateAsset(*buildingPrefab, nullptr, buildingPreview->transform.localPosition);
					auto bo = bgo->GetComponent<BuildingObject>();
					bo->building = Construction::ConstructBuilding(currentHoveredTile->tile, archBuildings[selected].first);

					bgo->GetComponent<SpriteRenderer>()->SetSprite(Utility::spritePath(bo->building->archBuilding.sprite));

					if (Utility::Contains(currentValidTiles, currentHoveredTile->tile))
					{
						// Construct Building
					}
				}
				
			}
		}
	}
}
