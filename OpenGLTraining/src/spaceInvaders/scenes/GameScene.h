#pragma once
#include "Scene.h"
#include <entities/Player.h>
#include "entities/EnemyManager.h"

class GameScene : public Scene
{
private:
	Player* _player;
	EnemyManager _enemyManager;

	void ConfigurePhysicsLayers() const;

public:
	GameScene(const std::string& name);
	void SpawnPlayer();
	void OnUpdate() override;
};

