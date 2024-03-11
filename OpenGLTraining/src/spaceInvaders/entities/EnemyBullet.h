#pragma once
#include "Bullet.h"
class EnemyBullet : public Bullet
{

private:
	void InitialConfig();

public:
	EnemyBullet(Guid guid);
	EnemyBullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
};

