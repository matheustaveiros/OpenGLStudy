#include "GameScene.h"
#include "audio/SoundEngine.h"
#include "ScreenManager.h"

void GameScene::ConfigurePhysicsLayers() const
{
	using enum PhysicsLayer::Layer;
	PhysicsLayer::SetLayerCollision(Default, std::vector<PhysicsLayer::Layer>{Default, Player, Enemy, Scenario});
	PhysicsLayer::SetLayerCollision(Player, std::vector<PhysicsLayer::Layer>{Enemy, Scenario});
	PhysicsLayer::SetLayerCollision(Enemy, std::vector<PhysicsLayer::Layer>{Player, Scenario});
	PhysicsLayer::SetLayerCollision(Scenario, std::vector<PhysicsLayer::Layer>{None});
}

void GameScene::CreateGameUI()
{
	_gameScreen = ScreenManager::CreateScreen<GameScreen>("game_screen");
	_gameScreen->SetPlayerHealth(_player->GetCurrentHealth(), _player->GetMaxHealth());
	_gameScreen->SetPlayerScore(0);
}

GameScene::GameScene(const std::string& name) : Scene(name)
{
	ConfigurePhysicsLayers();
	SpawnPlayer();
	_enemyManager.SpawnEnemies();
	SoundEngine::Play2DAudio(SoundEngine::Sounds::Music, true);
	CreateGameUI();
}

void GameScene::SpawnPlayer()
{
	glm::vec3 position{ 480,10,0 };
	glm::vec2 rotation{ 0,0 };
	glm::vec2 scale{ 1,1 };
	_player = InstantiateGameObject<Player>(position, rotation, scale);
}

void GameScene::OnUpdate()
{
	_enemyManager.Update();
}
