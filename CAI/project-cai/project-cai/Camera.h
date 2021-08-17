#pragma once

#ifndef CAMERA_H
#define CAMERA_H

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
		struct Display;

		class Camera : public Component
		{
		public:

			Camera();
			Camera(GameObject* _gameObject, Display* _display, Vector2f _resolution, float _size);
			Camera(const Camera& that);
			~Camera();

			Camera* Clone() override;

			void Update(float _elapsedTime) override;

			void Input(float _elapsedTime, RenderWindow& _window);
			void E_Input(float _elapsedTime, Event& _event, RenderWindow& _window);

			void setSize(float _value); float getSize();
			Display* display;

			int ppu() { return (int)(displayResolution.y / (size * 2)); }

		private:

			float speed = 0.4f;
			float scrollSpeed = 7;
			bool isDrag;
			Vector2f capturedMousePos;
			float moveSpeed = 0.4f;
			
			float size;

			Vector2f displayResolution;
		};

	}
}

#endif // !CAMERA_H
