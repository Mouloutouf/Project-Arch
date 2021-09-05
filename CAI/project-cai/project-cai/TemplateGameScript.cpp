#include "TemplateGameScript.h"

namespace alpha
{
	namespace game
	{
		TGameScript::TGameScript()
		{
		}
		TGameScript::TGameScript(int _field1, float _field2, char* _field3)
			: field1(_field1), field2(_field2), field3(_field3)
		{
		}
		TGameScript::TGameScript(const TGameScript& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject), field1(that.field1), field2(that.field2), field3(that.field3)
		{
		}

		TGameScript::~TGameScript()
		{
		}

		TGameScript* TGameScript::Clone(GameObject* _gameObject)
		{
			return new TGameScript(*this, _gameObject);
		}

		void TGameScript::Init()
		{
		}

		void TGameScript::Start()
		{
		}
		void TGameScript::Update(float _elapsedTime)
		{
		}
		void TGameScript::EventUpdate(Event& _event, float _elapsedTime)
		{
		}
	}
}
