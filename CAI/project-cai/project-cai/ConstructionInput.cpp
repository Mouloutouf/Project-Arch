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
			buildingsSprites = map<int, pair<BuildingType, string>>
			{
				{ 0, { BuildingType::DroneBay, DRONE_BAY_BUILDING.sprite } },
				{ 1, { BuildingType::Pharmacy, PHARMACY_BUILDING.sprite } },
				{ 2, { BuildingType::Prefabs, PREFABS_BUILDING.sprite } },
				{ 3, { BuildingType::Shed, SHED_BUILDING.sprite } },
				{ 4, { BuildingType::Storage, STORAGE_BUILDING.sprite } },
				{ 5, { BuildingType::Farm, FARM_BUILDING.sprite } }
			};
		}

		void ConstructionInput::Start()
		{
		}
		void ConstructionInput::Update(float _elapsedTime)
		{
			scrollThroughBuildings = Keyboard::isKeyPressed(Keyboard::LShift);

			Vector2f mouseWorldPos = display.ScreenToWorldPosition((Vector2f)Mouse::getPosition(*display.gameWindow->window));

			Vector2f buildingSelectedPos = mouseWorldPos + offsetFromMouse;
			buildingSelectedObject->transform.localPosition = buildingSelectedPos;

			Vector2f buildingPreviewPos = Vector2f(round(mouseWorldPos.x), round(mouseWorldPos.y));
			buildingPreviewObject->transform.localPosition = buildingPreviewPos;
		}
		void ConstructionInput::EventUpdate(Event& _event, float _elapsedTime)
		{
			if (scrollThroughBuildings) {
				if (_event.type == Event::MouseWheelScrolled)
				{
					float ticks = _event.mouseWheelScroll.delta;

					selectedBuildingType += (int)ticks;
					if (selectedBuildingType >= buildingsSprites.size()) selectedBuildingType = (int)buildingsSprites.size() - 1;
					if (selectedBuildingType < 0) selectedBuildingType = 0;

					buildingSelectedObject->GetComponent<SpriteRenderer>()->SetSprite(ASSETS_FOLDER + buildingsSprites[selectedBuildingType].second + ".png");
				}
			}
		}
	}
}
