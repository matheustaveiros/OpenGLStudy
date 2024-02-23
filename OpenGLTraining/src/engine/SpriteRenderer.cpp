#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const std::string& texturePath, glm::vec3 size)
{
	_texture = std::make_unique<Texture>("PLACE_HOLDER_PATH");
	_size = size;
}
