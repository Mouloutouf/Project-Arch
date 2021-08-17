#pragma once

#ifndef SCRIPT_BEHAVIOUR_H
#define SCRIPT_BEHAVIOUR_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameObject.h"
#include "Component.h"

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

		private:

		};
	}
}

#endif // !SCRIPT_BEHAVIOUR_H
