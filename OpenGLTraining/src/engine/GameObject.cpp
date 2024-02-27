#include "GameObject.h"

GameObject::GameObject(Guid guid, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::string& texturePath, glm::vec3 spriteSize)
{
	_guid = guid;
	_transform = std::make_unique<Transform>(position, rotation, scale);
	Shader tempShader("res/shaders/Basic.shader");

	_spriteRenderer = std::make_unique<SpriteRenderer>(texturePath, spriteSize, _transform.get(), tempShader);
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
}

void GameObject::OnPostRenderUpdate()
{
}

void GameObject::OnDestroy()
{
}
