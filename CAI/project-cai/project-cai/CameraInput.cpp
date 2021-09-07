#include "CameraInput.h"

namespace alpha
{
	namespace game
	{
		CameraInput::CameraInput(Camera* _camera, RenderWindow& _window)
			: camera(_camera), window(_window)
		{
		}
		CameraInput::CameraInput(const CameraInput& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject), camera(that.camera), window(that.window)
		{
		}

		CameraInput* CameraInput::Clone(GameObject* _gameObject)
		{
			return new CameraInput(*this, _gameObject);
		}

		void CameraInput::Start()
		{
		}

		void CameraInput::Update(float _elapsedTime)
		{
			if (Keyboard::isKeyPressed(Keyboard::Z)) {
				camera->gameObject->transform.localPosition.y += _elapsedTime * moveSpeed;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				camera->gameObject->transform.localPosition.y -= _elapsedTime * moveSpeed;
			}
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				camera->gameObject->transform.localPosition.x -= _elapsedTime * moveSpeed;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				camera->gameObject->transform.localPosition.x += _elapsedTime * moveSpeed;
			}

			if (isDrag) {
				Vector2f dragPos;

				Vector2f currentMousePos = (Vector2f)Mouse::getPosition(window);
				currentMousePos = Vector2f(currentMousePos.x - window.getSize().x, window.getSize().y - currentMousePos.y);
				currentMousePos /= (float)camera->pixelsPerUnit();

				Vector2f mouseMoveOffset = capturedMousePos - currentMousePos;
				dragPos = camera->gameObject->transform.localPosition + mouseMoveOffset;

				camera->gameObject->transform.localPosition = dragPos;

				capturedMousePos = currentMousePos;
			}
		}

		void CameraInput::EventUpdate(Event& _event, float _elapsedTime)
		{
			if (_event.type == Event::MouseWheelScrolled) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) return;
				float ticks = _event.mouseWheelScroll.delta;
				camera->setSize(camera->getSize() - (ticks * _elapsedTime * scrollSpeed));
			}

			if (_event.type == Event::MouseButtonPressed) {
				if (_event.mouseButton.button == Mouse::Right) {
					isDrag = true;

					capturedMousePos = (Vector2f)Mouse::getPosition(window);
					capturedMousePos = Vector2f(capturedMousePos.x - window.getSize().x, window.getSize().y - capturedMousePos.y);
					capturedMousePos /= (float)camera->pixelsPerUnit();
				}
			}
			if (_event.type == Event::MouseButtonReleased) {
				if (_event.mouseButton.button == Mouse::Right) {
					isDrag = false;
				}
			}
		}
	}
}