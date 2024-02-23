#pragma once
#include "Scene.h"
#include <entities/Player.h>
#include <entities/Enemy.h>

class GameScene : public Scene
{
private:
	Player* _player;
	std::vector<Enemy*> _enemies;

public:
	GameScene(const std::string& name);
};

