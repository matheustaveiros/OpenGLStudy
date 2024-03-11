#include "Enemy.h"
#include "ResourcesLoader.h"

void Enemy::InitialConfig()
{
	GetSpriteRenderer()->SetSpriteSize({ 30, 24 });
	TextureLoaderData& textureData = ResourcesLoader::GetTexture("EnemySprite", "res/textures/invader.png");
	GetSpriteRenderer()->SetTexture(textureData.GetTexture(), textureData.Slot);
	SetLayer(PhysicsLayer::Layer::Enemy);
}

Enemy::Enemy(Guid guid) : GameObject(guid)
{
	InitialConfig();
}

Enemy::Enemy(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
	: GameObject(guid, position, rotation, scale)
{
	InitialConfig();
}

void Enemy::OnCollisionEnter(GameObject* other)
{
	SetActive(false);
	other->SetActive(false);
	//spawn explosion
}
