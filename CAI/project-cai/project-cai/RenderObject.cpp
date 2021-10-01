#include "RenderObject.h"

namespace alpha
{
	namespace core
	{
		RenderObject::RenderObject(int _ppu)
			: ppu(_ppu)
		{
		}

#pragma region Text Object
		TextObject::TextObject(int _ppu, std::string _string, Color _color)
			: RenderObject(_ppu), string(_string), color(_color)
		{
			font.loadFromFile(TEXT_FONT);
			text = Text(_string, font, _ppu);
			text.setFillColor(_color);

			drawables.push_back(&text);
		}
		TextObject::TextObject(const TextObject& that)
			: RenderObject(that), string(that.string), color(that.color), font(that.font), text(that.text)
		{
			drawables.push_back(&text);
		}
		void TextObject::SetString(std::string _string) { string = _string; text.setString(_string); }
		void TextObject::SetCharacterSize(int _size) { ppu = _size; text.setCharacterSize(_size); }
		void TextObject::SetColor(Color _color) { color = _color; text.setFillColor(_color); }
#pragma endregion

#pragma region Sprite Object
		SpriteObject::SpriteObject(int _ppu, string _spritePath)
			: RenderObject(_ppu), spritePath(_spritePath)
		{
			SetSprite(_spritePath);
		}
		SpriteObject::SpriteObject(int _ppu, Texture _texture)
			: RenderObject(_ppu), texture(_texture)
		{
			sprite.setTexture(texture);

			drawables.push_back(&sprite);
		}
		SpriteObject::SpriteObject(const SpriteObject& that)
			: RenderObject(that), spritePath(that.spritePath), texture(that.texture), sprite(that.sprite)
		{
			drawables.push_back(&sprite);
		}
		void SpriteObject::SetSprite(string _spritePath)
		{
			if (!_spritePath.empty()) {
				spritePath = _spritePath;
				texture.loadFromFile(_spritePath);
				sprite.setTexture(texture);

				drawables.push_back(&sprite);
			}
		}
		Vector2f SpriteObject::GetSize()
		{
			return Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
		}
#pragma endregion

#pragma region UI Sprite Object
		UISpriteObject::UISpriteObject(int _ppu, string _spritePath)
			: SpriteObject(_ppu, _spritePath)
		{
			if (spritePath.empty()) {
				shape = RectangleShape(Vector2f(ppu, ppu));
				drawables.push_back(&shape);
			}
		}
		UISpriteObject::UISpriteObject(int _ppu, Texture _texture)
			: SpriteObject(_ppu, _texture)
		{
		}
		UISpriteObject::UISpriteObject(const UISpriteObject& that)
			: SpriteObject(that), outlineColor(that.outlineColor), outlineThickness(that.outlineThickness), shape(that.shape)
		{
			drawables.clear();
			if (!spritePath.empty())
				drawables.push_back(&sprite);
			if (spritePath.empty() || HasOutline())
				drawables.push_back(&shape);
		}
		void UISpriteObject::SetOutline(float _thickness, Color _color)
		{
			if (!Utility::Contains(drawables, (Drawable*)&shape)) {
				shape = RectangleShape(Vector2f(ppu, ppu));
				shape.setFillColor(Color::Transparent);
				drawables.push_back(&shape);
			}
			shape.setOutlineThickness(_thickness);
			shape.setOutlineColor(_color);
		}
		bool UISpriteObject::HasOutline() { return outlineThickness > 0; }
#pragma endregion

	}
}
