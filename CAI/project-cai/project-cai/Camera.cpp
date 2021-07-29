#include "Camera.h"

#pragma region Camera
Camera::Camera()
{
}
Camera::Camera(GameObject* _gameObject, Display* _display, Vector2i _resolution, float _size)
: Component(_gameObject), display(_display), displayResolution(_resolution), size(_size)
{
}

Camera::~Camera()
{
}

#pragma endregion
