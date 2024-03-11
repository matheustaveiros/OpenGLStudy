#include "GameScene.h"

void GameScene::ConfigurePhysicsLayers() const
{
	using enum PhysicsLayer::Layer;
	PhysicsLayer::SetLayerCollision(Default, std::vector<PhysicsLayer::Layer>{Default, Player, Enemy, Scenario});
	PhysicsLayer::SetLayerCollision(Player, std::vector<PhysicsLayer::Layer>{Enemy, Scenario});
	PhysicsLayer::SetLayerCollision(Enemy, std::vector<PhysicsLayer::Layer>{Player, Scenario});
	PhysicsLayer::SetLayerCollision(Scenario, std::vector<PhysicsLayer::Layer>{None});
}

GameScene::GameScene(const std::string& name) : Scene(name)
{
	ConfigurePhysicsLayers();
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
