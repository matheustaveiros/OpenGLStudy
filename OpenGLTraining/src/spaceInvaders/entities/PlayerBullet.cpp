#include "PlayerBullet.h"
void PlayerBullet::InitialConfig()
{
	SetBulletSprite("PlayerBullet", "res/textures/laser.png", { 4.0f, 16.0f });
	SetDirection(1);
	SetLayer(PhysicsLayer::Layer::Player);
}
PlayerBullet::PlayerBullet(Guid guid) : Bullet(guid)
{
	InitialConfig();
}

PlayerBullet::PlayerBullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
	: Bullet(guid, position, rotation, scale)
{
	InitialConfig();
}