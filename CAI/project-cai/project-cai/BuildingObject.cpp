#include "BuildingObject.h"

namespace alpha
{
	namespace game
	{
		BuildingObject::BuildingObject()
		{
		}
		BuildingObject::BuildingObject(Building* _building, SpriteRenderer* _spriteRenderer)
			: building(_building), spriteRenderer(_spriteRenderer)
		{
		}
		BuildingObject::BuildingObject(const BuildingObject& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject), building(that.building)
		{
			spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
		}

		BuildingObject::~BuildingObject()
		{
		}

		BuildingObject* BuildingObject::Clone(GameObject* _gameObject)
		{
			return new BuildingObject(*this, _gameObject);
		}

		void BuildingObject::Init()
		{
		}

		void BuildingObject::Start()
		{
		}
		void BuildingObject::Update(float _elapsedTime)
		{
			building->Process(_elapsedTime);
		}
		void BuildingObject::EventUpdate(Event& _event, float _elapsedTime)
		{
		}
	}
}
