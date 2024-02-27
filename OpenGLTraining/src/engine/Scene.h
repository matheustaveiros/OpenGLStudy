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
	Scene(const std::string& name);

	inline std::string_view GetName() { return _name; }

	template <typename T>
	T* Instantiate(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string& texturePath, glm::vec3 spriteSize);
	void Destroy(Guid guid);

	void Awake();
	void Start();
	void UpdateInput();
	void UpdatePhysics();
	void Update();
	void Render();
	void PostRenderUpdate();
};

template<typename T>
T* Scene::Instantiate(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string& texturePath, glm::vec3 spriteSize)
{
	Guid newGuid{};
	_gameObjectsMap.emplace(newGuid, std::make_unique<T>(newGuid, position, rotation, scale, texturePath, spriteSize));

	return dynamic_cast<T*>(_gameObjectsMap[newGuid].get());
}

