#include "EnemyManager.h"
#include "GameTime.h"
#include "../utils/RandomHelper.h"
#include <AppWindow.h>

void EnemyManager::SpawnEnemies()
{
	const float startOffsetX = 25.0f;
	glm::vec3 enemyPosition{ startOffsetX,500,0 };
	glm::vec3 enemySpriteSize{ 30,24,1 };
	const float enemyOffsetX = 10;
	const float enemyOffsetY = 10;
	const int enemiesPerLine = 23;
	const unsigned int enemyAmount = 92;

	for (size_t i = 0; i < enemyAmount; i++)
	{
		if (i > 0 && i % enemiesPerLine == 0)
		{
			enemyPosition.x = startOffsetX;
			enemyPosition.y -= enemySpriteSize.y + enemyOffsetY;
		}

		Enemy* newEnemy = _enemyPool.GetObject();
		newEnemy->GetTransform()->SetPosition(enemyPosition);

		enemyPosition.x += enemySpriteSize.x + enemyOffsetX;
	}
}

void EnemyManager::HandleBulletSpawn()
{
	EnemyBullet* newBullet = _enemyBulletPool.GetObject();
	Enemy* randomEnemy = GetRandomEnemyAlive();
	
	if (randomEnemy == nullptr)
		return;

	glm::vec3 bulletPos = randomEnemy->GetTransform()->GetPosition();
	bulletPos.x += BulletSpawnOffsetX;
	bulletPos.y += BulletSpawnOffsetY;
	newBullet->GetTransform()->SetPosition(bulletPos);
	newBullet->SetActive(true);
}

void EnemyManager::Update()
{
	_shootTime += GameTime::DeltaTime;

	if(_shootDelay > ShootMinDelay)
		_shootDelay -= GameTime::DeltaTime * ShootIncreaseRate;

	if (_shootTime >= _shootDelay)
	{
		_shootTime = 0.0f;
		HandleBulletSpawn();
	}

	ManageBulletsLifetime();
}

Enemy* EnemyManager::GetRandomEnemyAlive()
{
	std::vector<int> validIndexes;
	for (int i = 0; i < _enemyPool.GetPoolSize(); i++)
	{
		auto [isAvailableOnPool, enemy] = _enemyPool.GetObjectAndState(i);
		if (isAvailableOnPool == false && enemy->IsActive())
		{
			validIndexes.push_back(i);
		}
	}

	if (validIndexes.empty())
		return nullptr;

	int random = RandomHelper::Range<int>(0, static_cast<int>(validIndexes.size() - 1));

	return _enemyPool.AccessObjectByIndex(validIndexes[random]);
}

void EnemyManager::ManageBulletsLifetime()
{
	for (int i = 0; i < _enemyBulletPool.GetPoolSize(); i++)
	{
		auto [isAvailableOnPool, bullet] = _enemyBulletPool.GetObjectAndState(i);
		if (isAvailableOnPool == false)
		{
			const float bottomOffset = -50.0f;
			if (bullet->GetTransform()->GetPosition().y < bottomOffset)
			{
				_enemyBulletPool.Release(bullet);
			}
		}
	}
}