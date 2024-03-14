#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "GameObject.h"
#include "Guid.h"
#include "render/Text.h"
#include "glm/glm.hpp"

class Scene
{
private:
	std::string _name;
	std::unordered_map<Guid, std::unique_ptr<GameObject>, GUIDHash> _gameObjectsMap;

public:
	inline static Scene* ActiveScene;

	explicit Scene(const std::string& name);
	virtual ~Scene();

	std::string_view GetName() const { return _name; }

	template <typename T>
	T* InstantiateGameObject();
	template <typename T>
	T* InstantiateGameObject(glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	void DestroyGameObject(Guid guid);

	void Awake();
	virtual void OnAwake();
	void Start();
	virtual void OnStart();
	void UpdateInput();
	virtual void OnUpdateInput();
	void UpdatePhysics();
	virtual void OnUpdatePhysics();
	void Update();
	virtual void OnUpdate();
	void Render();
	virtual void OnRender();
	void PostRenderUpdate();
	virtual void OnPostRenderUpdate();
};

template<typename T>
T* Scene::InstantiateGameObject()
{
	Guid newGuid{};
	_gameObjectsMap.emplace(newGuid, std::make_unique<T>(newGuid));

	return dynamic_cast<T*>(_gameObjectsMap[newGuid].get());
}

template<typename T>
T* Scene::InstantiateGameObject(glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
{
	Guid newGuid{};
	_gameObjectsMap.emplace(newGuid, std::make_unique<T>(newGuid, position, rotation, scale));

	return dynamic_cast<T*>(_gameObjectsMap[newGuid].get());
}