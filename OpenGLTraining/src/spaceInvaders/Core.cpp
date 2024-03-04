#include "Core.h"
#include "glm/ext/matrix_transform.hpp"

float leftBorder = 0.0f, rightBorder = 960.0f;
float bottomBorder = 0.0f, topBorder = 540.0f;
float zNear = -1.0f, zFar = 1.0f;
glm::mat4 Core::Proj = glm::ortho(leftBorder, rightBorder, bottomBorder, topBorder, zNear, zFar);
glm::mat4 Core::View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

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


