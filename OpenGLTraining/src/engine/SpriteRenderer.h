#pragma once

#include "glm/glm.hpp"
#include <memory>
#include "Transform.h"
#include "..\Texture.h"
#include "..\Shader.h"
#include "..\IndexBuffer.h"
#include "..\VertexArray.h"
#include "..\VertexBuffer.h"
#include "..\VertexBufferLayout.h"

class SpriteRenderer
{
private:
	glm::vec3 _size;
	Transform* _transform;
	Shader* _shader;

	std::unique_ptr<Texture> _texture;
	std::unique_ptr<VertexArray> _vao;
	std::unique_ptr<VertexBuffer> _vbo;
	std::unique_ptr<IndexBuffer> _ibo;

public:
	SpriteRenderer(const std::string& texturePath, glm::vec3 size, Transform* transform, Shader* shader);
	void Draw();
};

