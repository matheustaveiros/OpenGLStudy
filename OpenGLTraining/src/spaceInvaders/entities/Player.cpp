#include "Player.h"

Player::Player(Guid guid, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string& texturePath, glm::vec3 spriteSize) 
	: GameObject(guid, position, rotation, scale, texturePath, spriteSize)
{
}
