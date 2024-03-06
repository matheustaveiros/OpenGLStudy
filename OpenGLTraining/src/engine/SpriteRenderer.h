#pragma once

#include "glm/glm.hpp"
#include <memory>
#include "Transform.h"
#include "../Texture.h"
#include "../Shader.h"
#include "../IndexBuffer.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"

class SpriteRenderer
{
private:
	glm::vec2 _spriteSize;
	Transform* _transform;
	Shader* _shader;
	const Texture* _texture;
	unsigned int _textureSlot;
	glm::vec4 _color{ 1.0f,1.0f,1.0f,1.0f };

	std::unique_ptr<VertexArray> _vao;
	std::unique_ptr<VertexBuffer> _vbo;
	std::unique_ptr<IndexBuffer> _ibo;

public:
	SpriteRenderer(Transform* transform, Shader* shader);
	void SetSpriteSize(glm::vec2 spriteSize) { _spriteSize = spriteSize; }
	void SetTexture(const Texture* texture, unsigned int slot);
	void SetColor(glm::vec4 color) { _color = color; }
	void Draw();
};

