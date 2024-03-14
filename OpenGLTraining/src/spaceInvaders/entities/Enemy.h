#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
private:
	void InitialConfig();

public:
	explicit Enemy(Guid guid);
	Enemy(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	~Enemy() = default;
	void OnCollisionEnter(GameObject* other) override;
};

