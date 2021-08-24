#include "ScriptBehaviour.h"

namespace alpha
{
	namespace core
	{
		ScriptBehaviour::ScriptBehaviour()
		{
		}
		ScriptBehaviour::ScriptBehaviour(GameObject* _gameObject)
			: Component(_gameObject)
		{
		}
		ScriptBehaviour::ScriptBehaviour(const ScriptBehaviour& that, GameObject* _gameObject)
			: Component(that, _gameObject)
		{
		}

		ScriptBehaviour::~ScriptBehaviour()
		{
		}

		ScriptBehaviour* ScriptBehaviour::Clone(GameObject* _gameObject)
		{
			return new ScriptBehaviour(*this,_gameObject);
		}

		void ScriptBehaviour::Start()
		{
		}

		void ScriptBehaviour::Update(float _elapsedTime)
		{
		}
		void ScriptBehaviour::EventUpdate(Event& _event, float _elapsedTime)
		{
		}
	}
}
