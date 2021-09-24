#include "RenderObject.h"

namespace alpha
{
	namespace core
	{
		RenderObject::RenderObject(int _ppu)
			: ppu(_ppu)
		{
		}

		TextObject::TextObject(int _ppu, std::string _string, Color _color)
			: RenderObject(_ppu), string(_string), color(_color)
		{
			font.loadFromFile(TEXT_FONT);
			text = Text(_string, font, _ppu);
			text.setFillColor(_color);

			drawable = &text;
		}
		TextObject::TextObject(const TextObject& that)
			: RenderObject(that), string(that.string), color(that.color), font(that.font), text(that.text)
		{
			drawable = &text;
		}
		void TextObject::SetString(std::string _string) { string = _string; text.setString(_string); }
		void TextObject::SetCharacterSize(int _size) { ppu = _size; text.setCharacterSize(_size); }
		void TextObject::SetColor(Color _color) { color = _color; text.setFillColor(_color); }

		SpriteObject::SpriteObject(int _ppu, string _spritePath)
			: RenderObject(_ppu), spritePath(_spritePath)
		{
			SetSprite(_spritePath);

			drawable = &sprite;
		}
		SpriteObject::SpriteObject(int _ppu, Texture _texture)
			: RenderObject(_ppu), texture(_texture)
		{
			sprite.setTexture(texture);

			drawable = &sprite;
		}
		SpriteObject::SpriteObject(const SpriteObject& that)
			: RenderObject(that), spritePath(that.spritePath), texture(that.texture), sprite(that.sprite)
		{
			drawable = &sprite;
		}
		void SpriteObject::SetSprite(string _spritePath)
		{
			if (!_spritePath.empty()) {
				spritePath = _spritePath;
				texture.loadFromFile(_spritePath);
				sprite.setTexture(texture);
			}
		}
		Vector2f SpriteObject::GetSize()
		{
			return Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
		}
	}
}
