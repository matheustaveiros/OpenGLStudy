#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy(Guid guid, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string& texturePath, glm::vec3 spriteSize);
};

