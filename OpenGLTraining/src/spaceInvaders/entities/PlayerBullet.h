#pragma once
#include "Bullet.h"
class PlayerBullet : public Bullet
{
private:
	void InitialConfig();
public:
	PlayerBullet(Guid guid);
	PlayerBullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
};

