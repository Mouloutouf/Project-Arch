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
			ScriptBehaviour(const ScriptBehaviour& that);
			~ScriptBehaviour();

			ScriptBehaviour* Clone() override;

			void Start() override;
			void Update(float _elapsedTime) override;
		};
	}
}

#endif // !SCRIPT_BEHAVIOUR_H
