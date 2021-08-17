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
		ScriptBehaviour::ScriptBehaviour(const ScriptBehaviour& that)
			: Component(that)
		{
		}

		ScriptBehaviour::~ScriptBehaviour()
		{
		}

		ScriptBehaviour* ScriptBehaviour::Clone()
		{
			return new ScriptBehaviour(*this);
		}

		void ScriptBehaviour::Start()
		{
		}

		void ScriptBehaviour::Update(float _elapsedTime)
		{
		}
	}
}
