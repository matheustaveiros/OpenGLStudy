#include "EnemyBullet.h"
#include "ResourcesLoader.h"

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

	std::vector<TextureLoaderData*> textures;
	textures.reserve(2);
	TextureLoaderData& textureData1 = ResourcesLoader::GetTexture("EnemyLaser0", "res/textures/laser_0.png");
	TextureLoaderData& textureData2 = ResourcesLoader::GetTexture("EnemyLaser1", "res/textures/laser_1.png");

	textures.push_back(&textureData1);
	textures.push_back(&textureData2);

	_textureAnimation = std::make_unique<TextureAnimation>(GetSpriteRenderer(), textures, 10.0f);

	SetDirection(-1);
	SetVelocity(200.0f);
	SetLayer(PhysicsLayer::Layer::Enemy);
}

void EnemyBullet::OnUpdate()
{
	Bullet::OnUpdate();
	_textureAnimation->Update();
}