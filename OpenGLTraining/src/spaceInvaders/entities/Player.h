#pragma once
#include "GameObject.h"
#include "ObjectPooling.h"
#include "PlayerBullet.h"
#include "events/OnEnemyDestroyedEvent.h"

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

	int ScorePerKill{ 10 };
	int _score{ 0 };

	ObjectPooling<PlayerBullet> _bulletPool;
	std::vector <std::shared_ptr<PlayerBullet>> _bullets;

	void InitialConfig();
	void SpawnProjectile();
	void OnEnemyDestroyed(const OnEnemyDestroyedEvent& args);

public:
	explicit Player(Guid guid);
	Player(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	~Player();
	void OnUpdate() override;
	void OnUpdateInput() override;
	void OnCollisionEnter(GameObject* other) override;
	void ManageBulletsLifetime();
	int GetMaxHealth() const { return MaxHealth; }
	int GetCurrentHealth() const { return _health; }
};

