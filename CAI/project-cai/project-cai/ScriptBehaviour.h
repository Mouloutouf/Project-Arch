#pragma once

#ifndef SCRIPT_BEHAVIOUR_H
#define SCRIPT_BEHAVIOUR_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

#include "AssetManager.h"

namespace alpha
{
	namespace core
	{
		class ScriptBehaviour : public Component
		{
		public:

			ScriptBehaviour();
			ScriptBehaviour(GameObject* _gameObject);
			ScriptBehaviour(const ScriptBehaviour& that, GameObject* _gameObject);
			~ScriptBehaviour();

			ScriptBehaviour* Clone(GameObject* _gameObject) override;

			void Start() override;
			void Update(float _elapsedTime) override;
			void EventUpdate(Event& _event, float _elapsedTime) override;
		};
	}
}

#endif // !SCRIPT_BEHAVIOUR_H
