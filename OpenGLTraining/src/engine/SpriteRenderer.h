#pragma once

#include "../Texture.h"
#include "glm/glm.hpp"
#include <memory>
class SpriteRenderer
{
private:
	std::unique_ptr<Texture> _texture;
	glm::vec3 _size;

public:
	SpriteRenderer(const std::string& texturePath, glm::vec3 size);
	void Draw();
};

