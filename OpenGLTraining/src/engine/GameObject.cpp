#include "GameObject.h"

GameObject::GameObject(Guid guid) : _guid{ guid }
{
	_transform = std::make_unique<Transform>(glm::vec3{0.0f,0.0f, 0.0f}, glm::vec2{ 0.0f,0.0f }, glm::vec2{ 1.0f, 1.0f });
	_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
	_spriteRenderer = std::make_unique<SpriteRenderer>(_transform.get(), _shader.get());
	_isActive = true;
}

GameObject::GameObject(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale) : _guid{ guid }
{
	_transform = std::make_unique<Transform>(position, rotation, scale);
	_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
	_spriteRenderer = std::make_unique<SpriteRenderer>(_transform.get(), _shader.get());
	_isActive = true;
}

GameObject::~GameObject()
{
	OnDestroy();
}

void GameObject::OnAwake()
{
}

void GameObject::OnStart()
{
}

void GameObject::OnUpdateInput()
{
}

void GameObject::OnUpdatePhysics()
{
}

void GameObject::OnUpdate()
{
}

void GameObject::OnRender()
{
	if(IsActive())
		_spriteRenderer->Draw();
}

void GameObject::OnPostRenderUpdate()
{
}

void GameObject::OnDestroy()
{
}

void GameObject::OnCollide(GameObject* other)
{
	if (!_onCollisionList.contains(other->GetGuid()))
	{
		_onCollisionList.try_emplace(other->GetGuid(), other);
		OnCollisionEnter(other);
	}
	else
	{
		OnCollisionStay(other);
	}
}

void GameObject::OnExitCollision(GameObject* other)
{
	if (_onCollisionList.contains(other->GetGuid()))
	{
		auto iterator = _onCollisionList.find(other->GetGuid());
		_onCollisionList.erase(iterator);
		OnCollisionExit(other);
	}
}

void GameObject::OnCollisionEnter(GameObject* other)
{	
}

void GameObject::OnCollisionStay(GameObject* other)
{	
}

void GameObject::OnCollisionExit(GameObject* other)
{
}
