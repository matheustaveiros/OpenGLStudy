#include "SpriteRenderer.h"
#include "..\Renderer.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include "Core.h"

SpriteRenderer::SpriteRenderer(const std::string& texturePath, glm::vec3 spriteSize, Transform* transform, Shader* shader)
{
    _vao = std::make_unique<VertexArray>();
	_texture = std::make_unique<Texture>(texturePath);
	_shader = shader;
	_spriteSize = spriteSize;
	_transform = transform;

    _texture->Bind();
    shader->Bind();
    shader->SetUniform1i("u_Texture", 0);
    shader->Unbind();


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
    glm::mat4 model{ 1.f };
    model = glm::translate(model, _transform->GetPosition());

    glm::vec2 size = _transform->GetScale() * _spriteSize;
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
    float rotate = 0.f;
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));

    model = glm::scale(model, glm::vec3(size, 1.f));

    _shader->Bind();
    _shader->SetUniformMat4f("u_MVP", Core::Proj * Core::View * model);
    _shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    _texture->Bind(0);

    _vao->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, _ibo->GetCount(), GL_UNSIGNED_INT, nullptr));
}
