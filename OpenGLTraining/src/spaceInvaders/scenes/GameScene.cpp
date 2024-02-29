#include "GameScene.h"

GameScene::GameScene(const std::string& name) : Scene(name)
{
	SpawnPlayer();
	SpawnEnemies();
}

void GameScene::SpawnPlayer()
{
	glm::vec3 position{ 0,0,0 };
	glm::vec3 rotation{ 0,0,0 };
	glm::vec3 scale{ 1,1,1 };
	glm::vec3 spriteSize{ 100,100,1 };
	_player = Instantiate<Player>(position, rotation, scale, "res/textures/cool_texture.png", spriteSize);
}

void GameScene::SpawnEnemies()
{
	glm::vec3 enemyPosition{ 0,0,0 };
	glm::vec3 enemyRotation{ 0,0,0 };
	glm::vec3 enemyScale{ 1,1,1 };
	glm::vec3 enemySpriteSize{ 100,100,1 };

	for (size_t i = 0; i < 10; i++)
	{
		_enemies.emplace_back(Instantiate<Enemy>(enemyPosition, enemyRotation, enemyScale, "res/textures/cool_texture.png", enemySpriteSize));
		enemyPosition.x += 10;
	}
}
