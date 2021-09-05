#include "ConstructionInput.h"

namespace alpha
{
	namespace game
	{
		ConstructionInput::ConstructionInput(Display& _display)
			: display(_display), offsetFromMouse(Vector2f(0.4f, 0.4f))
		{
		}
		ConstructionInput::ConstructionInput(const ConstructionInput& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject), display(that.display), offsetFromMouse(that.offsetFromMouse)
		{
		}

		ConstructionInput* ConstructionInput::Clone(GameObject* _gameObject)
		{
			return new ConstructionInput(*this, _gameObject);
		}

		void ConstructionInput::Init()
		{
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
			buildingSelectedObject = AssetManager::InstantiateAsset(GameObject("Selected Building"));
			buildingSelectedObject->AddComponent(new SpriteRenderer(buildingSelectedObject, AssetManager::currentSceneDisplay, archBuildings[selected].second.sprite, 16));
			buildingSelectedObject->transform.localScale /= 2.0f;

			buildingPreviewObject = AssetManager::InstantiateAsset(GameObject("Preview Building"));
			buildingPreviewObject->AddComponent(new SpriteRenderer(buildingPreviewObject, AssetManager::currentSceneDisplay, archBuildings[selected].second.sprite, 16));
			Color transparent = Color(255, 255, 255, 128);
			buildingPreviewObject->GetComponent<SpriteRenderer>()->GetSprite()->setColor(transparent);
		}
		void ConstructionInput::Update(float _elapsedTime)
		{
			scrollThroughBuildings = Keyboard::isKeyPressed(Keyboard::LShift);

			currentMousePosition = display.ScreenToWorldPosition((Vector2f)Mouse::getPosition(*display.gameWindow->window));

			Vector2f buildingSelectedPos = currentMousePosition + offsetFromMouse;
			buildingSelectedObject->transform.localPosition = buildingSelectedPos;

			Vector2f buildingPreviewPos = Vector2f(round(currentMousePosition.x), round(currentMousePosition.y));
			buildingPreviewObject->transform.localPosition = buildingPreviewPos;

			hoveredTile = grid->GetTile(buildingPreviewPos.x, buildingPreviewPos.y);

			// Display available and unavailable tiles, potential exploited tiles, and potential structures destruction

		}
		void ConstructionInput::EventUpdate(Event& _event, float _elapsedTime)
		{
			if (scrollThroughBuildings) {
				if (_event.type == Event::MouseWheelScrolled)
				{
					float ticks = _event.mouseWheelScroll.delta;

					selected += (int)ticks;
					if (selected >= archBuildings.size()) selected = (int)archBuildings.size() - 1;
					if (selected < 0) selected = 0;

					buildingSelectedObject->GetComponent<SpriteRenderer>()->SetSprite(ASSETS_FOLDER + archBuildings[selected].second.sprite + ".png");
					buildingPreviewObject->GetComponent<SpriteRenderer>()->SetSprite(ASSETS_FOLDER + archBuildings[selected].second.sprite + ".png");
				}
			}

			if (_event.type == Event::MouseButtonPressed) {
				if (_event.mouseButton.button == sf::Mouse::Left) {

					if (hoveredTile == nullptr) return;
					//Temp
					auto bgo = AssetManager::InstantiateAsset(*buildingPrefab, buildingPreviewObject->transform.localPosition);
					auto bo = bgo->GetComponent<BuildingObject>();
					bo->building = Construction::ConstructBuilding(hoveredTile->tile, archBuildings[selected].first);

					if (Utility::Contains(currentValidTiles, hoveredTile->tile))
					{
						// Construct Building
					}
				}
				
			}
		}
	}
}
