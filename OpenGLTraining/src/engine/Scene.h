#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "GameObject.h"
#include "Guid.h"
#include "glm/glm.hpp"
class Scene
{
private:
	std::string _name;
	std::unordered_map<Guid, std::unique_ptr<GameObject>, GUIDHash> _gameObjectsMap;

public:
	inline static Scene* ActiveScene;

	Scene(const std::string& name);

	inline std::string_view GetName() const { return _name; }

	template <typename T>
	T* Instantiate();

	template <typename T>
	T* Instantiate(glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);

	void Destroy(Guid guid);

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
T* Scene::Instantiate()
{
	Guid newGuid{};
	_gameObjectsMap.emplace(newGuid, std::make_unique<T>(newGuid));

	return dynamic_cast<T*>(_gameObjectsMap[newGuid].get());
}

template<typename T>
T* Scene::Instantiate(glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
{
	Guid newGuid{};
	_gameObjectsMap.emplace(newGuid, std::make_unique<T>(newGuid, position, rotation, scale));

	return dynamic_cast<T*>(_gameObjectsMap[newGuid].get());
}