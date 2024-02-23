#include "GameLoop.h"

void GameLoop::EntryPoint()
{
	//temp
	_activeScene = std::make_unique<Scene>("GameScene");

	_activeScene->Awake();
	_activeScene->Start();

	_isRunning = true;
	Loop();
}

void GameLoop::Loop()
{
	while (_isRunning)
	{
		_activeScene->UpdateInput();
		_activeScene->UpdatePhysics();
		_activeScene->Update();
		_activeScene->Render();
		_activeScene->PostRenderUpdate();
	}
}