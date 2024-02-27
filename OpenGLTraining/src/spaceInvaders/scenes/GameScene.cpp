#include "GameScene.h"

GameScene::GameScene(const std::string& name) : Scene(name)
{
	//spawn player
	glm::vec3 position{ 0,0,0 };
	glm::vec3 rotation{ 0,0,0 };
	glm::vec3 scale{ 0,0,0 };
	glm::vec3 spriteSize{ 0,0,0 };
	_player = Instantiate<Player>(position, rotation, scale, "res/textures/cool_texture.png", spriteSize);


	//spawn enemies
	for (size_t i = 0; i < 10; i++)
	{
		glm::vec3 enemyPosition{ 0,0,0 };
		glm::vec3 enemyRotation{ 0,0,0 };
		glm::vec3 enemyScale{ 0,0,0 };
		glm::vec3 enemySpriteSize{ 0,0,0 };
		_enemies.emplace_back(Instantiate<Enemy>(enemyPosition, enemyRotation, enemyScale, "res/textures/cool_texture.png", enemySpriteSize));
	}
}
