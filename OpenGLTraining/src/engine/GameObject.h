#pragma once

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Guid.h"
#include <memory>

class GameObject
{
private:
	bool _isActive{ false };
	Guid _guid;
	std::unique_ptr<Transform> _transform;
	std::unique_ptr<SpriteRenderer> _spriteRenderer;
	std::unique_ptr<Shader> _shader;

public:
	GameObject(Guid guid);
	GameObject(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	~GameObject();
	inline Guid GetGuid() const { return _guid; }
	inline Transform* GetTransform() { return _transform.get(); }
	inline SpriteRenderer* GetSpriteRenderer() { return _spriteRenderer.get(); }
	inline void SetActive(bool state) { _isActive = state; }
	inline bool IsActive() { return _isActive; }

	virtual void OnAwake();
	virtual void OnStart();
	virtual void OnUpdateInput();
	virtual void OnUpdatePhysics();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnPostRenderUpdate();
	virtual void OnDestroy();
};

