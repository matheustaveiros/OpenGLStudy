#pragma once
#include "GameObject.h"
#include "ObjectPooling.h"
#include "PlayerBullet.h"

class Player : public GameObject
{
private:
	const float ShootDelay{ 0.7f };
	const float LeftBorderOffset = 10.0f;
	const float RightBorderOffset = 40.0f;
	const float BulletSpawnOffsetX = 14.0f;
	const float BulletSpawnOffsetY = 16.0f;

	float _velocity{ 250.0f };
	float _direction{ 0.0f };
	float _shootTime{ 0.0f };

	int _health{ 0 };
	const int MaxHealth{ 3 };

	ObjectPooling<PlayerBullet> _bulletPool;
	std::vector <std::shared_ptr<PlayerBullet>> _bullets;

	void InitialConfig();
	void SpawnProjectile();

public:
	Player(Guid guid);
	Player(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	void OnUpdate() override;
	void OnUpdateInput() override;
	void OnCollisionEnter(GameObject* other) override;

	void ManageBulletsLifetime();
};

