#pragma once
#include "scenes/GameScene.h"
#include <memory>
class Core
{
private:
	std::unique_ptr<GameScene> _gameScene;

public:
	void Awake();
	void Start();
	void UpdateInput();
	void UpdatePhysics();
	void Update();
	void Render();
	void PostRenderUpdate();
};

