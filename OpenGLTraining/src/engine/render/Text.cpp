#include "Text.h"
#include "ShaderManager.h"
#include "VertexBufferLayout.h"
#include "FontManager.h"
#include "Font.h"

void Text::InitialConfig()
{
    _vertexArray.Bind();
    _vertexBuffer = VertexBuffer(nullptr, sizeof(float) * 6 * 4);

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.Push<float>(4);

    _vertexArray.AddBuffer(_vertexBuffer, vertexBufferLayout);

    _vertexBuffer.Unbind();
    _vertexArray.Unbind();
    _font = FontManager::GetFont("default");
}

Text::Text()
{
    InitialConfig();
}

void Text::SetCharacterSize(float size)
{
    _size = size;
}

void Text::SetString(const std::string& text)
{
    _text = text;
}

void Text::SetFont(Font* font)
{
    _font = font;
}

void Text::SetPosition(Vector2f position)
{
    _position = position;
}

void Text::SetFillColor(Color color)
{
    _color = color;
}

void Text::Draw()
{
    //void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)

    // activate corresponding render state	
    _shader.Bind();
    _shader.SetUniform3f("textColor", _color.GetRGB().x, _color.GetRGB().y, _color.GetRGB().z);
    glActiveTexture(GL_TEXTURE0);
    _vertexArray.Bind();

    float x = _position.x;

    //m_Size = 1;

    // iterate through all characters
    std::string::const_iterator c;
    for (c = _text.begin(); c != _text.end(); c++)
    {
        Character ch = _font->GetCharacters()[*c];

        float xpos = x + ch.Bearing.x * _size;
        float ypos = _position.y + (_font->GetCharacters()['H'].Bearing.y - ch.Bearing.y) * _size;

        float w = ch.Size.x * _size;
        float h = ch.Size.y * _size;

        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // update content of VBO memory
        _vertexBuffer.Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
        _vertexBuffer.Unbind();
        
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // now advance cursors for next glyph
        // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
        x += (ch.Advance >> 6) * _size;
    }

    _vertexArray.Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}