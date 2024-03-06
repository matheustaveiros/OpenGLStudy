#include "GameScene.h"

GameScene::GameScene(const std::string& name) : Scene(name)
{
	SpawnPlayer();
	SpawnEnemies();
}

void GameScene::SpawnPlayer()
{
	glm::vec3 position{ 480,10,0 };
	glm::vec2 rotation{ 0,0 };
	glm::vec2 scale{ 1,1 };
	_player = Instantiate<Player>(position, rotation, scale);
}

void GameScene::SpawnEnemies()
{
	glm::vec3 enemyPosition{ 0,540,0 };
	glm::vec2 enemyRotation{ 0,0 };
	glm::vec2 enemyScale{ 1,1 };
	glm::vec3 enemySpriteSize{ 30,24,1 };
	const float enemyOffsetX = 10;
	const float enemyOffsetY = 10;
	const int enemiesPerLine = 20;
	const unsigned int enemyAmount = 100;

	for (size_t i = 0; i < enemyAmount; i++)
	{
		if (i > 0 && i % enemiesPerLine == 0)
		{
			enemyPosition.x = 0;
			enemyPosition.y -= enemySpriteSize.y + enemyOffsetY;
		}

		_enemies.emplace_back(Instantiate<Enemy>(enemyPosition, enemyRotation, enemyScale));

		enemyPosition.x += enemySpriteSize.x + enemyOffsetX;
	}
}
