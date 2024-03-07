#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy(Guid guid);
	Enemy(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
};

