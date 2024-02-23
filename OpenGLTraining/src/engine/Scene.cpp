#include "Scene.h"

Scene::Scene(const std::string& name) : _name { name }
{
}

template<typename T>
T* Scene::Instantiate(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string& texturePath, glm::vec3 spriteSize)
{
	Guid newGuid{};
	_gameObjectsMap.emplace(newGuid, std::make_unique<T>(newGuid, position, rotation, scale, texturePath, spriteSize));

	return _gameObjectsMap[newGuid].get();
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