#pragma once
#include "Bullet.h"
class PlayerBullet : public Bullet
{
public:
	PlayerBullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
};

