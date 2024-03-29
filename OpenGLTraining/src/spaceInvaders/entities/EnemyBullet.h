#pragma once
#include "Bullet.h"
#include "render/TextureAnimation.h"
#include <memory>

class EnemyBullet : public Bullet
{

private:
	std::unique_ptr<TextureAnimation> _textureAnimation;
	void InitialConfig();

public:
	explicit EnemyBullet(Guid guid);
	EnemyBullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	~EnemyBullet() = default;
	void OnUpdate() override;
};

