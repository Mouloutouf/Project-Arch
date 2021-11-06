#include "RenderObject.h"

namespace alpha
{
	namespace core
	{
		RenderObject::RenderObject()
			: ppu(100)
		{
		}
		RenderObject::RenderObject(int _ppu)
			: ppu(_ppu)
		{
		}

		RenderObject::~RenderObject()
		{
		}

#pragma region Text Object
		TextObject::TextObject(int _ppu, std::string _string, Color _color)
			: RenderObject(_ppu), string(_string), color(_color)
		{
			Create(_string, _color);
		}
		TextObject::TextObject(const TextObject& that)
			: RenderObject(that), string(that.string), color(that.color), font(that.font), text(that.text)
		{
			drawables.clear();
			drawables.push_back(&spriteText);
		}

		TextObject::~TextObject()
		{
		}

		void TextObject::Create(std::string _string, Color _color)
		{
			font.loadFromFile(TEXT_FONT);
			text = Text(_string, font, ppu);
			text.setFillColor(_color);

			drawables.push_back(&spriteText);
		}

		void TextObject::SetString(std::string _string) { string = _string; text.setString(_string); }
		void TextObject::SetCharacterSize(int _size) { ppu = _size; text.setCharacterSize(_size); }
		void TextObject::SetColor(Color _color) { color = _color; text.setFillColor(_color); }
#pragma endregion

#pragma region Sprite Object
		SpriteObject::SpriteObject()
			: RenderObject()
		{
		}
		SpriteObject::SpriteObject(int _ppu, string _spritePath)
			: RenderObject(_ppu), spritePath(_spritePath)
		{
			Create(_spritePath);
		}
		SpriteObject::SpriteObject(int _ppu, Texture _texture)
			: RenderObject(_ppu), texture(_texture)
		{
			Create(_texture);
		}
		SpriteObject::SpriteObject(const SpriteObject& that)
			: RenderObject(that), spritePath(that.spritePath), texture(that.texture), sprite(that.sprite)
		{
			drawables.clear();
			drawables.push_back(&sprite);
		}

		void SpriteObject::Create(string _spritePath)
		{
			SetSprite(_spritePath);
			drawables.push_back(&sprite);
		}
		void SpriteObject::Create(Texture _texture)
		{
			SetSprite(_texture);
			drawables.push_back(&sprite);
		}

		SpriteObject::~SpriteObject()
		{
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
#pragma endregion

#pragma region UI Sprite Object
		UISpriteObject::UISpriteObject(int _ppu, string _spritePath)
		{
			ppu = _ppu;
			Create(_spritePath);
		}
		UISpriteObject::UISpriteObject(int _ppu, Texture _texture)
		{
			ppu = _ppu;
			Create(_texture);
		}
		UISpriteObject::UISpriteObject(const UISpriteObject& that)
			: SpriteObject(that), outlineColor(that.outlineColor), outlineThickness(that.outlineThickness), shape(that.shape), hasSprite(that.hasSprite), hasShape(that.hasShape)
		{
			drawables.clear();
			if (hasSprite)
				drawables.push_back(&sprite);
			if (hasShape)
				drawables.push_back(&shape);
		}

		UISpriteObject::~UISpriteObject()
		{
		}

		void UISpriteObject::Create(string _spritePath)
		{
			SetSprite(_spritePath);

			if (spritePath.empty()) {
				shape = RectangleShape(Vector2f(ppu, ppu));
				drawables.push_back(&shape);
				hasShape = true;
			}
			else {
				drawables.push_back(&sprite);
				hasSprite = true;
			}
		}
		void UISpriteObject::Create(Texture _texture)
		{
			SpriteObject::Create(_texture);
			hasSprite = true;
		}

		void UISpriteObject::SetOutline(float _thickness, Color _color)
		{
			if (!hasShape) {
				shape = RectangleShape(Vector2f(ppu, ppu));
				shape.setFillColor(Color::Transparent);
				drawables.push_back(&shape);
				hasShape = true;
			}
			shape.setOutlineThickness(-_thickness);
			shape.setOutlineColor(_color);
		}
		bool UISpriteObject::HasOutline() { return outlineThickness > 0; }

		void UISpriteObject::SetColor(Color _color)
		{
			if (hasSprite)
				sprite.setColor(_color);
			else
				shape.setFillColor(_color);
		}
#pragma endregion

	}
}
