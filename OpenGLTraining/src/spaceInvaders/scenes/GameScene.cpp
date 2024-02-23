#include "GameScene.h"

GameScene::GameScene(const std::string& name) : Scene(name)
{
	//spawn player
	_player = Instantiate<Player>(glm::vec3{}, glm::vec3{}, glm::vec3{}, "TexturePath", glm::vec3{});

	//spawn enemies
	for (size_t i = 0; i < 10; i++)
	{
		_enemies.emplace_back(Instantiate<Enemy>(glm::vec3{}, glm::vec3{}, glm::vec3{}, "TexturePath", glm::vec3{}));
	}
}
