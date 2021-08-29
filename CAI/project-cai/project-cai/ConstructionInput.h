#pragma once

#ifndef CONSTRUCTION_INPUT_H
#define CONSTRUCTION_INPUT_H

#include "Alpha.h"

///\

#include "Display.h"
#include "ScriptBehaviour.h"
#include "Construction.h"

namespace alpha
{
	using namespace core;

	namespace game
	{
		class ConstructionInput : public ScriptBehaviour
		{
		public:

			ConstructionInput(Display& _display);
			ConstructionInput(const ConstructionInput& that, GameObject* _gameObject);

			ConstructionInput* Clone(GameObject* _gameObject) override;

			void Init() override;

			void Start() override;
			void Update(float _elapsedTime) override;
			void EventUpdate(Event& _event, float _elapsedTime) override;

		private:

			Display& display;

			map<int, pair<BuildingType, string>> buildingsSprites;

			Vector2f offsetFromMouse;
			GameObject* buildingSelectedObject = nullptr;
			GameObject* buildingPreviewObject = nullptr;

			int selectedBuildingType = 0;
			bool scrollThroughBuildings = false;
		};
	}
}

#endif // !CONSTRUCTION_INPUT_H
