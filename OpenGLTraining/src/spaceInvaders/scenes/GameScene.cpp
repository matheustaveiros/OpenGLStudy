#include "GameScene.h"

GameScene::GameScene(const std::string& name) : Scene(name)
{
	SpawnPlayer();
	_enemyManager.SpawnEnemies();
}

void GameScene::SpawnPlayer()
{
	glm::vec3 position{ 480,10,0 };
	glm::vec2 rotation{ 0,0 };
	glm::vec2 scale{ 1,1 };
	_player = Instantiate<Player>(position, rotation, scale);
}

void GameScene::OnUpdate()
{
	_enemyManager.Update();
}
