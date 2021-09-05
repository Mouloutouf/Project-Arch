#pragma once

#ifndef TEMPLATE_GAME_SCRIPT_H
#define TEMPLATE_GAME_SCRIPT_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Game.h"

/// Other #includes

namespace alpha
{
	using namespace core;

	namespace game
	{
		class TGameScript : public ScriptBehaviour
		{
		public:

			TGameScript();
			TGameScript(int _field1, float _field2, char* _field3);
			TGameScript(const TGameScript& that, GameObject* _gameObject);
			~TGameScript();

			TGameScript* Clone(GameObject* _gameObject) override;

			void Init() override;

			void Start() override;
			void Update(float _elapsedTime) override;
			void EventUpdate(Event& _event, float _elapsedTime) override;

			int field1;
			float field2;
			char* field3;
		};
	}
}

#endif // !TEMPLATE_GAME_SCRIPT_H
