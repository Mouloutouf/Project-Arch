#include "Camera.h"

#pragma region Camera
Camera::Camera()
{
}
Camera::Camera(GameObject* _gameObject, Display* _display, Vector2f _resolution, float _size)
	: Component(_gameObject), display(_display), displayResolution(_resolution), size(_size)
{
}
Camera::Camera(const Camera& that)
	: Component(that), display(that.display), displayResolution(that.displayResolution), size(that.size)
{
}

Camera::~Camera()
{
}

Camera* Camera::Clone()
{
	return new Camera(*this);
}

void Camera::Update(float _elapsedTime)
{
}

void Camera::Input()
{
}

#pragma endregion
