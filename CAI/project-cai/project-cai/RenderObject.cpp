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
		TextObject::TextObject(int _ppu)
			: RenderObject(_ppu)
		{
			Create(_ppu);
		}
		TextObject::TextObject(int _ppu, std::string _string, Color _color)
			: RenderObject(_ppu), string(_string), color(_color)
		{
			Create(_ppu, _string, _color);
		}
		TextObject::TextObject(const TextObject& that)
			: RenderObject(that), string(that.string), color(that.color), font(that.font), text(that.text)
		{
			drawables.clear();
			drawables.push_back(&text);
		}
		void TextObject::Create(int _ppu)
		{
			Create(_ppu, "New Text", Color::White);
		}
		void TextObject::Create(int _ppu, std::string _string, Color _color)
		{
			font.loadFromFile(TEXT_FONT);
			text = Text(_string, font, _ppu);
			text.setFillColor(_color);

			drawables.push_back(&text);
		}
		void TextObject::SetString(std::string _string) { string = _string; text.setString(_string); }
		void TextObject::SetCharacterSize(int _size) { ppu = _size; text.setCharacterSize(_size); }
		void TextObject::SetColor(Color _color) { color = _color; text.setFillColor(_color); }
#pragma endregion

#pragma region Sprite Object
		SpriteObject::SpriteObject(int _ppu)
			: RenderObject(_ppu)
		{
		}
		SpriteObject::SpriteObject(int _ppu, string _spritePath)
			: RenderObject(_ppu), spritePath(_spritePath)
		{
			SetSprite(_spritePath);

			drawables.push_back(&sprite);
		}
		SpriteObject::SpriteObject(int _ppu, Texture _texture)
			: RenderObject(_ppu), texture(_texture)
		{
			SetSprite(_texture);

			drawables.push_back(&sprite);
		}
		SpriteObject::SpriteObject(const SpriteObject& that)
			: RenderObject(that), spritePath(that.spritePath), texture(that.texture), sprite(that.sprite)
		{
			drawables.clear();
			drawables.push_back(&sprite);
		}
		void SpriteObject::SetSprite(string _spritePath)
		{
			if (!_spritePath.empty()) {
				spritePath = _spritePath;
				texture.loadFromFile(_spritePath);
				sprite.setTexture(texture);
			}
		}
		void SpriteObject::SetSprite(Texture _texture)
		{
			sprite.setTexture(texture);
		}
		Vector2f SpriteObject::GetSize()
		{
			return Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
		}
		void SpriteObject::Create(int _ppu)
		{
			Create(_ppu, DEFAULT_SPRITE);
		}
		void SpriteObject::Create(int _ppu, string _spritePath)
		{
			SetSprite(_spritePath);

			drawables.push_back(&sprite);
		}
		void SpriteObject::Create(int _ppu, Texture _texture)
		{
			SetSprite(_texture);

			drawables.push_back(&sprite);
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
		void UISpriteObject::SetColor(Color _color)
		{
			if (!spritePath.empty())
				sprite.setColor(_color);
			else
				shape.setFillColor(_color);
		}
#pragma endregion

	}
}
