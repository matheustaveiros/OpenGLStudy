#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
private:
	void InitialConfig();

public:
	Enemy(Guid guid);
	Enemy(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	void OnCollisionEnter(GameObject* other) override;
};

