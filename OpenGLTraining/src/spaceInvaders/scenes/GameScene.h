#pragma once
#include "Scene.h"
#include <entities/Player.h>
#include "entities/EnemyManager.h"
#include "screens/GameScreen.h"

class GameScene : public Scene
{
private:
	Player* _player{ nullptr };
	GameScreen* _gameScreen{ nullptr };
	EnemyManager _enemyManager;

	void ConfigurePhysicsLayers() const;
	void CreateGameUI();

public:
	explicit GameScene(const std::string& name);
	~GameScene() = default;
	void SpawnPlayer();
	void OnUpdate() override;
};

