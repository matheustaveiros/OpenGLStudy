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
	
	int _currentDirection{ 1 };
	const float EnemyMoveXRange{ 400.0f };
	const float EnemyMoveYRange{ -400.0f };
	const float BoundsWidthOffsetLeft{ 3.0f };
	const float BoundsWidthOffsetRight{ -33.0f };
	const float BoundsHeightOffset{ 10.0f };

	float _enemyMoveDelay{ 1.0f };
	float _enemyMoveTime{ 0.0f };
	const float EnemyMoveIncreaseRatio{ 0.01f };
	const float MinMoveDelay{ 0.1f };

	Enemy* GetRandomEnemyAlive();
	void ManageBulletsLifetime();
	void DoEnemyMove();
	void MoveAllEnemiesDown();
	bool IsOutOfBoundsHorizontal(glm::vec3 pos) const;
	bool IsOutOfBoundsBottom(glm::vec3 pos) const;

public:
	void SpawnEnemies();
	void HandleBulletSpawn();
	void Update();
};