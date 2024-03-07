#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	float _velocity{ 300.0f };
	int _direction{ 0 };

protected:
	void SetBulletSprite(const std::string& textureKey, const std::string& texturePath, glm::vec2 spriteSize);
	void SetDirection(int direction) { _direction = direction; }

public:
	Bullet(Guid guid);
	Bullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	void OnUpdate() override;
};

