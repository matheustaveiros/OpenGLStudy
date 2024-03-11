#pragma once

#include "Enemy.h"
#include "EnemyBullet.h"
#include "ObjectPooling.h"
class EnemyManager
{
private:
	ObjectPooling<Enemy> _enemyPool;
	ObjectPooling<EnemyBullet> _enemyBulletPool;
	float _shootDelay{ 4.0f };
	float _shootTime{ 0.0f };
	const float ShootIncreaseRate{ 0.008f };
	const float ShootMinDelay{ 0.25f };
	const float BulletSpawnOffsetX{ 13.0f };
	const float BulletSpawnOffsetY{ -15.0f };

	Enemy* GetRandomEnemyAlive();

public:
	void SpawnEnemies();
	void HandleBulletSpawn();
	void Update();
	
};