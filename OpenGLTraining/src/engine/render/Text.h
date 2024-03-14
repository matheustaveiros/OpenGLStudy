#pragma once
#include "Color.h"
#include "Drawable.h"
#include "Font.h"
#include "Vector2f.h"
#include <string>
#include "ShaderManager.h"
#include "VertexArray.h"
#include "Guid.h"

class Text : public Drawable
{
public:
	Text();

	void SetCharacterSize(float size);

	void SetString(const std::string& text);

	void SetFont(Font* font);

	void SetPosition(Vector2f position);

	void SetFillColor(Color color);

	void Draw() override;

private:
	void InitialConfig();

	Shader _shader = ShaderManager::GetShader("text");

	VertexArray _vertexArray;

	Color _color{ 1.0f, 1.0f, 1.0f, 1.0f };

	std::string _text;

	Vector2f _position{ 0.0f, 0.0f };

	float _size{ 1.0f };

	VertexBuffer _vertexBuffer;

	Font* _font;
};
