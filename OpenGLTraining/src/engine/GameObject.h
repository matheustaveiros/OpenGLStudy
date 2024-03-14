#pragma once

#include "Transform.h"
#include "../engine/render/SpriteRenderer.h"
#include "Guid.h"
#include <memory>
#include "physics/PhysicsLayer.h"
#include <iostream>
#include <typeinfo>
#include "render/ShaderManager.h"

class GameObject
{
private:
	bool _isActive{ false };
	Guid _guid;
	std::unique_ptr<Transform> _transform;
	std::unique_ptr<SpriteRenderer> _spriteRenderer;
	Shader& _shader{ ShaderManager::GetShader("sprite") };
	std::unordered_map<Guid, GameObject*, GUIDHash> _onCollisionList;
	PhysicsLayer::Layer _layer;

public:
	explicit GameObject(Guid guid);
	GameObject(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);
	virtual ~GameObject();
	Guid GetGuid() const { return _guid; }
	Transform* GetTransform() { return _transform.get(); }
	SpriteRenderer* GetSpriteRenderer() { return _spriteRenderer.get(); }
	void SetActive(bool state) { _isActive = state; }
	bool IsActive() const { return _isActive; }
	

	//Lifetime
	virtual void OnAwake();
	virtual void OnStart();
	virtual void OnUpdateInput();
	virtual void OnUpdatePhysics();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnPostRenderUpdate();
	virtual void OnDestroy();

	//Physics
	void OnCollide(GameObject* other);
	void OnExitCollision(GameObject* other);
	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other);
	virtual void OnCollisionExit(GameObject* other);
	const PhysicsLayer::Layer& GetLayer() const { return _layer; }
	void SetLayer(const PhysicsLayer::Layer& layer) { _layer = layer; }

	bool CanCollideWith(const GameObject* other) const
	{
		//check in global matrix using this object layer, if the other object layer is in.
		for (const PhysicsLayer::Layer& layer : PhysicsLayer::GetCollisionLayers(_layer))
		{
			if (layer == other->GetLayer())
			{
				return true;
			}
		}

		return false;
	}
};

