#include "Renderer.h"

#include <iostream>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);

    // GL_NO_ERROR is 0, we could write like this:
    // while(!glGetError());
}

bool GLLogCall(const char* Function, const char* File, int Line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << Function << " " << File << ":" << Line << "\n";
        return false;
    }

    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& Va, const IndexBuffer& Ib, const Shader& Shader) const
{
    Shader.Bind();
    Va.Bind();
    Ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, Ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}