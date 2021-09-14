#include "TextRenderer.h"

namespace alpha
{
	namespace core
	{
		TextRenderer::TextRenderer()
		{
		}
		TextRenderer::TextRenderer(GameObject* _gameObject, Display* _display, std::string _string, Color _color, int _characterSize, __Layer _layer)
			: Component(_gameObject), display(_display)
		{
			textObject = new TextObject(_characterSize, _string, _color);
			textObject->layer = _layer;

			AddToRender();
		}
		TextRenderer::TextRenderer(const TextRenderer& that, GameObject* _gameObject)
			: Component(that, _gameObject), display(that.display)
		{
			textObject = new TextObject(*that.textObject);

			AddToRender();
		}

		TextRenderer::~TextRenderer()
		{
			delete textObject;
		}

		void TextRenderer::AddToRender()
		{
			auto& tags = *(gameObject->GetTagsList());
			for (int i = 0; i < tags.size(); i++) {
				if (tags[i] == Tag::Prefab)
					return;
			} display->AddObjectToRender(gameObject, textObject);
		}

		void TextRenderer::SetString(string _string)
		{
			textObject->string = _string; textObject->text.setString(textObject->string);
		}

		TextRenderer* TextRenderer::Clone(GameObject* _gameObject)
		{
			return new TextRenderer(*this, _gameObject);
		}

		void TextRenderer::SetActive(bool _value)
		{
			Component::SetActive(_value);
			textObject->render = _value;
		}

		void TextRenderer::SetLayer(__Layer _layer)
		{
			textObject->layer = _layer;

			display->RemoveObjectToRender(textObject);
			AddToRender();
		}
		__Layer TextRenderer::GetLayer() { return textObject->layer; }

		void TextRenderer::SetOrderInLayer(int _order) { textObject->orderInLayer = clamp(_order, 0, 9999); }
		int TextRenderer::GetOrderInLayer() { return textObject->orderInLayer; }
	}
}
