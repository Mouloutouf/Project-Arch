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

			void SetCameraSize(float _value);

		private:

			Camera* camera;

			RenderWindow& window;

			float scrollSpeed = 14;
			float moveSpeed = 0.4f;

			float minCamSize = 4.0f, maxCamSize = 12.0f;

			bool isDrag = false;
			Vector2f capturedMousePos;
		};
	}
}

#endif // !CAMERA_INPUT_H
