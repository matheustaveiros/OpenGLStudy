#include "GameScreen.h"
#include "Scene.h"
#include <format>

GameScreen::GameScreen(Guid guid) : Screen(guid)
{
	_playerHealthText = InstantiateText();
	_scoreText = InstantiateText();
}

void GameScreen::SetPlayerScore(int score)
{
	_playerHealthText->setString(std::format("Score: {}", std::to_string(score)));
}

void GameScreen::SetPlayerHealth(int health, int maxHealth)
{
	_playerHealthText->setString(std::format("Health: {}/{}", std::to_string(health), std::to_string(maxHealth)));
}
