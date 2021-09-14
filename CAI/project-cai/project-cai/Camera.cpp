#include "Camera.h"

namespace alpha
{
	namespace core
	{
#pragma region Camera
		Camera::Camera()
		{
		}
		Camera::Camera(Display* _display, Vector2f _resolution, float _size, Color _backgroundColor)
			: display(_display), displayResolution(_resolution), size(_size), backgroundColor(_backgroundColor)
		{
		}
		Camera::Camera(const Camera& that, GameObject* _gameObject)
			: Component(that, _gameObject), display(that.display), displayResolution(that.displayResolution), size(that.size)
		{
		}

		Camera::~Camera()
		{
		}

		Camera* Camera::Clone(GameObject* _gameObject)
		{
			return new Camera(*this, _gameObject);
		}

		void Camera::setSize(float _value) {
			if (_value <= 0.0f) _value = 0.001f;
			size = _value;
		}
		float Camera::getSize() { return size; }
#pragma endregion
	}
}
