#include "EnemyManager.h"
#include "GameTime.h"
#include "../utils/RandomHelper.h"
#include <AppWindow.h>
#include "audio/SoundEngine.h"

void EnemyManager::SpawnEnemies()
{
	const float startOffsetX = 25.0f;
	glm::vec3 enemyPosition{ startOffsetX, 470,0 };
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

	SoundEngine::Play2DAudio(SoundEngine::Sounds::Shoot);
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
	DoEnemyMove();
}

void EnemyManager::DoEnemyMove()
{
	_enemyMoveTime += GameTime::DeltaTime;
	if (_enemyMoveTime < _enemyMoveDelay)
	{
		return;
	}

	_enemyMoveTime = 0.0f;

	if (_enemyMoveDelay > MinMoveDelay)
	{
		_enemyMoveDelay -= EnemyMoveIncreaseRatio;
		
		if (_enemyMoveDelay < MinMoveDelay)
			_enemyMoveDelay = MinMoveDelay;
	}

	bool shouldChangeDirection = false;
	for (int i = 0; i < _enemyPool.GetPoolSize(); i++)
	{
		Transform* transform = _enemyPool.AccessObjectByIndex(i)->GetTransform();
		glm::vec3 pos = transform->GetPosition();
		pos.x += static_cast<float>(_currentDirection) * GameTime::DeltaTime * EnemyMoveXRange;
		transform->SetPosition(pos);

		if (!shouldChangeDirection && IsOutOfBoundsHorizontal(pos))
		{
			shouldChangeDirection = true;
		}
	}

	if (shouldChangeDirection)
	{
		_currentDirection *= -1;
		MoveAllEnemiesDown();
	}

	SoundEngine::Play2DAudio(SoundEngine::Sounds::Descent);
}

void EnemyManager::MoveAllEnemiesDown()
{
	for (int i = 0; i < _enemyPool.GetPoolSize(); i++)
	{
		Transform* transform = _enemyPool.AccessObjectByIndex(i)->GetTransform();
		glm::vec3 pos = transform->GetPosition();
		pos.y += EnemyMoveYRange * GameTime::DeltaTime;
		transform->SetPosition(pos);

		if (IsOutOfBoundsBottom(pos))
		{
			//Destroy Enemy
			//Remove Player Life
		}
	}
}

bool EnemyManager::IsOutOfBoundsHorizontal(glm::vec3 pos) const
{
	if(pos.x > static_cast<float>(AppWindow::WindowWidth) + BoundsWidthOffsetRight)
		return true;
	if (pos.x < BoundsWidthOffsetLeft)
		return true;

	return false;
}

bool EnemyManager::IsOutOfBoundsBottom(glm::vec3 pos) const
{
	if (pos.y < BoundsHeightOffset)
		return true;

	return false;
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