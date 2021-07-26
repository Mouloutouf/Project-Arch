#include "Camera.h"

#pragma region Camera
Camera::Camera()
{
}
Camera::Camera(Display* _display, Vector2i _resolution)
: display(_display), displayResolution(_resolution)
{
}

Camera::~Camera()
{
}

#pragma endregion
