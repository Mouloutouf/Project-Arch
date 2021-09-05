#pragma once

#ifndef BUILDING_OBJECT_H
#define BUILDING_OBJECT_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Buildings.h"

namespace alpha
{
	using namespace core;

	namespace game
	{
		class BuildingObject : public ScriptBehaviour
		{
		public:

			BuildingObject();
			BuildingObject(Building* _building, SpriteRenderer* _spriteRenderer);
			BuildingObject(const BuildingObject& that, GameObject* _gameObject);
			~BuildingObject();

			BuildingObject* Clone(GameObject* _gameObject) override;

			void Init() override;

			void Start() override;
			void Update(float _elapsedTime) override;
			void EventUpdate(Event& _event, float _elapsedTime) override;

			Building* building;
			SpriteRenderer* spriteRenderer;
		};
	}
}

#endif // !BUILDING_OBJECT_H
