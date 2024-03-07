#include "Enemy.h"
#include "ResourcesLoader.h"

Enemy::Enemy(Guid guid) : GameObject(guid)
{
	GetSpriteRenderer()->SetSpriteSize({ 30, 24 });
	TextureLoaderData& textureData = ResourcesLoader::GetTexture("EnemySprite", "res/textures/invader.png");
	GetSpriteRenderer()->SetTexture(textureData.GetTexture(), textureData.Slot);
}

Enemy::Enemy(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
	: GameObject(guid, position, rotation, scale)
{
	GetSpriteRenderer()->SetSpriteSize({ 30, 24 });
	TextureLoaderData& textureData = ResourcesLoader::GetTexture("EnemySprite", "res/textures/invader.png");
	GetSpriteRenderer()->SetTexture(textureData.GetTexture(), textureData.Slot);
}
