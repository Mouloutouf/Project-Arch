#pragma once

#ifndef CAMERA_INPUT_H
#define CAMERA_INPUT_H

#include "Alpha.h"
#include "Core.h"

///\

namespace alpha
{
	using namespace core;

	namespace game
	{
		class CameraInput : public ScriptBehaviour
		{
		public:

			CameraInput(Camera* _camera, RenderWindow& _window);
			CameraInput(const CameraInput& that, GameObject* _gameObject);

			CameraInput* Clone(GameObject* _gameObject) override;

			void Start() override;
			void Update(float _elapsedTime) override;
			void EventUpdate(Event& _event, float _elapsedTime) override;

		private:

			Camera* camera;

			RenderWindow& window;

			float scrollSpeed = 7;
			float moveSpeed = 0.4f;
			bool isDrag = false;
			Vector2f capturedMousePos;
		};
	}
}

#endif // !CAMERA_INPUT_H
