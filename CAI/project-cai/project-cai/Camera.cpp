#include "Camera.h"

namespace alpha
{
	namespace core
	{
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

		void Camera::Input(float _elapsedTime, RenderWindow& _window)
		{
			if (Keyboard::isKeyPressed(Keyboard::Z)) {
				gameObject->transform.localPosition.y += _elapsedTime * speed;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				gameObject->transform.localPosition.y -= _elapsedTime * speed;
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				gameObject->transform.localPosition.x -= _elapsedTime * speed;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				gameObject->transform.localPosition.x += _elapsedTime * speed;
			}

			if (isDrag) {
				Vector2f dragPos;

				Vector2f currentMousePos = (Vector2f)Mouse::getPosition(_window);
				currentMousePos = Vector2f(currentMousePos.x - _window.getSize().x, _window.getSize().y - currentMousePos.y);
				currentMousePos /= (float)ppu();

				Vector2f mouseMoveOffset = capturedMousePos - currentMousePos;
				dragPos = gameObject->transform.localPosition + mouseMoveOffset;

				gameObject->transform.localPosition = dragPos;

				capturedMousePos = currentMousePos;
			}
		}

		void Camera::E_Input(float _elapsedTime, Event& _event, RenderWindow& _window)
		{
			if (_event.type == Event::MouseWheelScrolled) {
				float ticks = _event.mouseWheelScroll.delta;
				setSize(size - (ticks * _elapsedTime * scrollSpeed));
			}

			if (_event.type == Event::MouseButtonPressed) {
				if (_event.mouseButton.button == Mouse::Right) {
					isDrag = true;

					capturedMousePos = (Vector2f)Mouse::getPosition(_window);
					capturedMousePos = Vector2f(capturedMousePos.x - _window.getSize().x, _window.getSize().y - capturedMousePos.y);
					capturedMousePos /= (float)ppu();
				}
			}
			if (_event.type == Event::MouseButtonReleased) {
				if (_event.mouseButton.button == Mouse::Right) {
					isDrag = false;
				}
			}
		}

		void Camera::setSize(float _value) {
			if (_value <= 0.0f) _value = 0.001f;
			size = _value;
		}
		float Camera::getSize() { return size; }
#pragma endregion
	}
}
