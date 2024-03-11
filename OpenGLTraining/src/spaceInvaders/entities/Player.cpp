#include "Player.h"
#include "ResourcesLoader.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include "GameTime.h"
#include "AppWindow.h"
#include "Scene.h"

Player::Player(Guid guid) : GameObject(guid)
{
	InitialConfig();
}

Player::Player(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
	: GameObject(guid, position, rotation, scale)
{
	InitialConfig();
}

void Player::InitialConfig()
{
	_shootTime = ShootDelay;
	GetSpriteRenderer()->SetSpriteSize({ 32, 32 });
	TextureLoaderData& textureData = ResourcesLoader::GetTexture("PlayerSprite", "res/textures/fighter.png");
	GetSpriteRenderer()->SetTexture(textureData.GetTexture(), textureData.Slot);
	SetLayer(PhysicsLayer::Layer::Player);
	_health = MaxHealth;
}

void Player::OnUpdate()
{
	glm::vec3 position = GetTransform()->GetPosition();
	position.x += _direction * _velocity * GameTime::DeltaTime;
	GetTransform()->SetPosition(position);

	ManageBulletsLifetime();
}

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

	_shootTime += GameTime::DeltaTime;
	if (Input::GetKey(GLFW_KEY_SPACE) && _shootTime > ShootDelay)
	{
		SpawnProjectile();
		_shootTime = 0.0f;
	}
}

void Player::OnCollisionEnter(GameObject* other)
{
	other->SetActive(false);
	_health--;
	std::cout << "Player was Hit, current Life is: " << std::to_string(_health) << "\n";
	if (_health < 0)
	{
		std::cout << "Game Over\n";
		SetActive(false);
	}
}

void Player::ManageBulletsLifetime()
{
	for (int i = 0; i < _bulletPool.GetPoolSize(); i++)
	{
		auto[isAvailableOnPool, bullet] = _bulletPool.GetObjectAndState(i);
		if (isAvailableOnPool == false)
		{
			if (bullet->GetTransform()->GetPosition().y > AppWindow::WindowHeight)
			{
				_bulletPool.Release(bullet);
			}
		}
	}
}

void Player::SpawnProjectile()
{
	PlayerBullet* newBullet = _bulletPool.GetObject();
	_bullets.emplace_back(newBullet);

	glm::vec3 position = GetTransform()->GetPosition();
	position.x += BulletSpawnOffsetX;
	position.y += BulletSpawnOffsetY;
	
	newBullet->GetTransform()->SetPosition(position);
	newBullet->SetActive(true);
}