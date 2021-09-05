#include "TextRenderer.h"

namespace alpha
{
	namespace core
	{
		TextRenderer::TextRenderer()
		{
		}
		TextRenderer::TextRenderer(GameObject* _gameObject, Display* _display, std::string _string, Color _color, int _characterSize)
			: Component(_gameObject), string(_string), color(_color), characterSize(_characterSize), display(_display)
		{
			text = Text();
			text.setString(_string);
			text.setFillColor(_color);
			text.setCharacterSize(_characterSize);
		}
		TextRenderer::TextRenderer(const TextRenderer& that, GameObject* _gameObject)
			: Component(that, _gameObject), text(that.text), string(that.string), color(that.color), characterSize(that.characterSize), display(that.display)
		{
			text.setString(string);
			text.setFillColor(color);
			text.setCharacterSize(characterSize);
		}

		TextRenderer::~TextRenderer()
		{
		}

		TextRenderer* TextRenderer::Clone(GameObject* _gameObject)
		{
			return new TextRenderer(*this, _gameObject);
		}

		void TextRenderer::AddToRender()
		{
			auto& tags = *(gameObject->GetTagsList());
			for (int i = 0; i < tags.size(); i++) {
				if (tags[i] == Tag::Prefab)
					return;
			} display->AddTextToRender(gameObject, &text, characterSize);
		}
	}
}
