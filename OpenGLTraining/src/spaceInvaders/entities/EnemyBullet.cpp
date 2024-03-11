#include "EnemyBullet.h"
EnemyBullet::EnemyBullet(Guid guid) : Bullet(guid)
{
	InitialConfig();
}

EnemyBullet::EnemyBullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
	: Bullet(guid, position, rotation, scale)
{
	InitialConfig();
}

void EnemyBullet::InitialConfig()
{
	SetBulletSprite("EnemyBullet", "res/textures/laser.png", { 4.0f, 16.0f });
	SetDirection(-1);
	SetVelocity(200.0f);
}