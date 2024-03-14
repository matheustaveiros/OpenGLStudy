#include "GameScreen.h"
#include "Scene.h"
#include <format>
#include "AppWindow.h"

GameScreen::GameScreen(Guid guid) : Screen(guid)
{
	_scoreText = InstantiateText();
	_scoreText->setPosition(Vector2f{ AppWindow::WindowWidth - 150.0f, 10.0f });

	_playerHealthText = InstantiateText();
	_playerHealthText->setPosition(Vector2f{ 7.0f, AppWindow::WindowHeight - 20.0f});
}

void GameScreen::SetPlayerScore(int score)
{
	_scoreText->setString(std::format("Score: {}", std::to_string(score)));
}

void GameScreen::SetPlayerHealth(int health, int maxHealth)
{
	_playerHealthText->setString(std::format("Health: {}/{}", std::to_string(health), std::to_string(maxHealth)));
}
