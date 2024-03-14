#include "Enemy.h"
#include "ResourcesLoader.h"
#include <audio/SoundEngine.h>
#include "EventManager.h"
#include "events/OnEnemyDestroyedEvent.h"

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
	
	SoundEngine::Play2DAudio(SoundEngine::Sounds::Explosion);
	EventManager::Dispatch(OnEnemyDestroyedEvent());
}
