#include "Player.h"
#include "ResourcesLoader.h"

Player::Player(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale) 
	: GameObject(guid, position, rotation, scale)
{
	GetSpriteRenderer()->SetSpriteSize({ 32, 32 });
	TextureLoaderData& textureData = ResourcesLoader::GetTexture("PlayerSprite", "res/textures/fighter.png");
	GetSpriteRenderer()->SetTexture(textureData.GetTexture(), textureData.Slot);
}

void Player::OnUpdate()
{
	glm::vec3 position = GetTransform()->GetPosition();
	position.x += _direction * _velocity;
	GetTransform()->SetPosition(position);
}

void Player::OnUpdateInput()
{
	//if key pressed left
	//	_direction = -1.0f;
	//else if key pressed right
	//	_direction = 1.0f;
	//else _direction = 0f;
}
