#include "Text.h"
#include "ShaderManager.h"
#include "VertexBufferLayout.h"
#include "FontManager.h"
#include "Font.h"

void Text::InitialConfig()
{
    m_VertexArray.Bind();
    m_VertexBuffer = VertexBuffer(nullptr, sizeof(float) * 6 * 4);

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.Push<float>(4);

    m_VertexArray.AddBuffer(m_VertexBuffer, vertexBufferLayout);

    m_VertexBuffer.Unbind();
    m_VertexArray.Unbind();
    m_Font = FontManager::GetFont("default");
}

Text::Text()
{
    InitialConfig();
}

void Text::setCharacterSize(float size)
{
    m_Size = size;
}

void Text::setString(const std::string& text)
{
    m_Text = text;
}

void Text::setFont(Font* font)
{
    m_Font = font;
}

void Text::setPosition(Vector2f position)
{
    m_Position = position;
}

void Text::setFillColor(Color color)
{
    m_Color = color;
}

void Text::Draw()
{
    //void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)

    // activate corresponding render state	
    m_Shader.Bind();
    m_Shader.SetUniform3f("textColor", m_Color.getRGB().x, m_Color.getRGB().y, m_Color.getRGB().z);
    glActiveTexture(GL_TEXTURE0);
    m_VertexArray.Bind();

    float x = m_Position.x;

    //m_Size = 1;

    // iterate through all characters
    std::string::const_iterator c;
    for (c = m_Text.begin(); c != m_Text.end(); c++)
    {
        Character ch = m_Font->getCharacters()[*c];

        float xpos = x + ch.Bearing.x * m_Size;
        float ypos = m_Position.y + (m_Font->getCharacters()['H'].Bearing.y - ch.Bearing.y) * m_Size;

        float w = ch.Size.x * m_Size;
        float h = ch.Size.y * m_Size;

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
        m_VertexBuffer.Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
        m_VertexBuffer.Unbind();
        
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // now advance cursors for next glyph
        // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
        x += (ch.Advance >> 6) * m_Size;
    }

    m_VertexArray.Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}