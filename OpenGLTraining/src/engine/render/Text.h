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
	Text(Guid guid);

	void setCharacterSize(float size);

	void setString(const std::string& text);

	void setFont(Font* font);

	void setPosition(Vector2f position);

	void setFillColor(Color color);

	// Inherited via Drawable
	void Draw() override;

private:
	void InitialConfig();

	Shader m_Shader = ShaderManager::GetShader("text");

	VertexArray m_VertexArray;

	Color m_Color{ 1.0f, 1.0f, 1.0f, 1.0f };

	std::string m_Text;

	Vector2f m_Position{ 0.0f, 0.0f };

	float m_Size{ 1.0f };

	VertexBuffer m_VertexBuffer;

	Font* m_Font;

	Guid m_Guid;
};
