#include "Player.h"
#include "ResourcesLoader.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include "GameTime.h"
#include "AppWindow.h"

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
	position.x += _direction * _velocity * GameTime::DeltaTime;
	GetTransform()->SetPosition(position);
}

const float LeftBorderOffset = 10.0f;
const float RightBorderOffset = 40.0f;
void Player::OnUpdateInput()
{
	if (Input::GetKey(GLFW_KEY_A) || Input::GetKey(GLFW_KEY_LEFT))
	{
		if(GetTransform()->GetPosition().x > LeftBorderOffset)
			_direction = -1.0f;
		else
			_direction = 0.0f;
	}
	else if (Input::GetKey(GLFW_KEY_D) || Input::GetKey(GLFW_KEY_RIGHT))
	{
		if (GetTransform()->GetPosition().x < (float)AppWindow::WindowWidth - RightBorderOffset)
			_direction = 1.0f;
		else
			_direction = 0.0f;
	}
	else
	{
		_direction = 0.0f;
	}

	if (Input::GetKey(GLFW_KEY_SPACE))
	{
		//Spawn Projectile
	}

	std::cout << GetTransform()->GetPosition().x << std::endl;
}
