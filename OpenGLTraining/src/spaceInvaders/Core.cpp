#include "Core.h"

void Core::Awake()
{
	_gameScene = std::make_unique<GameScene>("GameScene");
	_gameScene->Awake();
}

void Core::Start()
{
	_gameScene->Start();
}

void Core::UpdateInput()
{
	_gameScene->UpdateInput();
}

void Core::UpdatePhysics()
{
	_gameScene->UpdatePhysics();
}

void Core::Update()
{
	_gameScene->Update();
}

void Core::Render()
{
	_gameScene->Render();
}

void Core::PostRenderUpdate()
{
	_gameScene->PostRenderUpdate();
}


