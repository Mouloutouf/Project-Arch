#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

namespace alpha
{
	namespace core
	{
		struct Display;

		class Camera : public Component
		{
		public:

			Camera();
			Camera(Display* _display, Vector2f _resolution, float _size);
			Camera(const Camera& that, GameObject* _gameObject);
			~Camera();

			Camera* Clone(GameObject* _gameObject) override;

			void setSize(float _value); float getSize();
			Display* display;

			int pixelsPerUnit() { return (int)(displayResolution.y / (size * 2)); }

		private:

			float size;

			Vector2f displayResolution;
		};

	}
}

#endif // !CAMERA_H
