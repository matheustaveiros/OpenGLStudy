#pragma once
#include "scenes/GameScene.h"
#include <glm/ext/matrix_clip_space.hpp>
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

	static glm::mat4 Proj;
	static glm::mat4 View;
};

