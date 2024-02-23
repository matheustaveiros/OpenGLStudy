#pragma once

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Guid.h"
#include <memory>

class GameObject
{
private:
	Guid _guid;
	std::unique_ptr<Transform> _transform;
	std::unique_ptr<SpriteRenderer> _spriteRenderer;

public:
	GameObject(Guid guid, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string& texturePath, glm::vec3 spriteSize);
	inline Guid GetGuid() const { return _guid; }
	inline Transform* GetTransform() { return _transform.get(); }
	inline SpriteRenderer* GetSpriteRenderer() { return _spriteRenderer.get(); }

	virtual void OnAwake() = 0;
	virtual void OnStart() = 0;
	virtual void OnUpdateInput() = 0;
	virtual void OnUpdatePhysics() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnPostRenderUpdate() = 0;
};

