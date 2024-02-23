#include "GameObject.h"

GameObject::GameObject(Guid guid, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string& texturePath, glm::vec3 spriteSize)
{
	_guid = guid;
	_transform = std::make_unique<Transform>(position, rotation, scale);
	_spriteRenderer = std::make_unique<SpriteRenderer>(texturePath, spriteSize);
}
