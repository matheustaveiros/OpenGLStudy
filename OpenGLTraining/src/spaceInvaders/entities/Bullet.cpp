#include "Bullet.h"
#include "ResourcesLoader.h"
#include "GameTime.h"

void Bullet::SetBulletSprite(const std::string& textureKey, const std::string& texturePath, glm::vec2 spriteSize)
{
	GetSpriteRenderer()->SetSpriteSize(spriteSize);
	TextureLoaderData& textureData = ResourcesLoader::GetTexture(textureKey, texturePath);
	GetSpriteRenderer()->SetTexture(textureData.GetTexture(), textureData.Slot);
}

Bullet::Bullet(Guid guid) : GameObject(guid)
{
}

Bullet::Bullet(Guid guid, glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
	: GameObject(guid, position, rotation, scale)
{
	
}

void Bullet::OnUpdate()
{
	glm::vec3 position = GetTransform()->GetPosition();
	position.y += (float)_direction * _velocity * GameTime::DeltaTime;
	GetTransform()->SetPosition(position);
}
