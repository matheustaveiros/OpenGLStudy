#include "SpriteRenderer.h"
#include "..\Renderer.h"
#include "glm/ext/matrix_transform.hpp"

SpriteRenderer::SpriteRenderer(const std::string& texturePath, glm::vec3 size, Transform* transform, Shader* shader)
{
	_texture = std::make_unique<Texture>(texturePath);
	_size = size;
	_transform = transform;
	_shader = shader;

    _vao = std::make_unique<VertexArray>();

    float vertices[] =
    {
        // Pos     UV
        0.f, 1.f,  0.f, 1.f,
        1.f, 1.f,  1.f, 1.f,
        1.f, 0.f,  1.f, 0.f,
        0.f, 0.f,  0.f, 0.f
    };

    _vbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

    VertexBufferLayout layout{};
    layout.Push<float>(2);
    layout.Push<float>(2);
    _vao->AddBuffer(*_vbo, layout);

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    _ibo = std::make_unique<IndexBuffer>(indices, 6);
}

void SpriteRenderer::Draw()
{
    _shader->Bind();

    glm::mat4 model{ 1.f };
    model = glm::translate(model, _transform->GetPosition());

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));

    model = glm::scale(model, glm::vec3(size, 1.f));

    _shader->SetUniformMat4f("u_Model", model);
    _shader->SetUniform3f("u_SpriteColor", color);

    _texture->Bind(0);

    m_VAO->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr));
}
