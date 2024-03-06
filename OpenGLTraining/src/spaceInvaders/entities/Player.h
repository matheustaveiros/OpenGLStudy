#pragma once
#include "GameObject.h"
class Player : public GameObject
{
private:
	float _velocity{ 5 };
	float _direction{ 0 };

public:
	Player(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	void OnUpdate() override;
	void OnUpdateInput() override;
};

