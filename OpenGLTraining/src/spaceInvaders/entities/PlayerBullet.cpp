#include "PlayerBullet.h"
PlayerBullet::PlayerBullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
	: Bullet(guid, position, rotation, scale)
{
	SetBulletSprite("PlayerBullet", "res/textures/laser.png", { 4.0f, 16.0f });
	SetDirection(1.0f);
}