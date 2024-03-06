#include "Scene.h"

Scene::Scene(const std::string& name) : _name { name }
{
	Scene::ActiveScene = this;
}

void Scene::Destroy(Guid guid)
{
	if (_gameObjectsMap.contains(guid))
	{
		auto iterator = _gameObjectsMap.find(guid);
		_gameObjectsMap.erase(iterator);
	}
	else
	{
		std::cout << "Unable to Destroy object, the object didn't exist in the scene" << std::endl;
	}
}

void Scene::Awake()
{
	for (auto& obj : _gameObjectsMap)
	{
		obj.second.get()->OnAwake();
	}
}

void Scene::Start()
{
	for (auto& obj : _gameObjectsMap)
	{
		obj.second.get()->OnStart();
	}
}

void Scene::UpdateInput()
{
	for (auto& obj : _gameObjectsMap)
	{
		obj.second.get()->OnUpdateInput();
	}
}

void Scene::UpdatePhysics()
{
	for (auto& obj : _gameObjectsMap)
	{
		obj.second.get()->OnUpdatePhysics();
	}
}

void Scene::Update()
{
	for (auto& obj : _gameObjectsMap)
	{
		obj.second.get()->OnUpdate();
	}
}

void Scene::Render()
{
	for (auto& obj : _gameObjectsMap)
	{
		obj.second.get()->OnRender();
	}
}

void Scene::PostRenderUpdate()
{
	for (auto& obj : _gameObjectsMap)
	{
		obj.second.get()->OnPostRenderUpdate();
	}
}
