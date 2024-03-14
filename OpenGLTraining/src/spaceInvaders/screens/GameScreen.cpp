#include "GameScreen.h"
#include "Scene.h"
#include <format>
#include "AppWindow.h"
#include "EventManager.h"


GameScreen::GameScreen(Guid guid) : Screen(guid)
{
	_scoreText = InstantiateText();
	_scoreText->SetPosition(Vector2f{ (float)AppWindow::WindowWidth - 150.0f, 10.0f });

	_playerHealthText = InstantiateText();
	_playerHealthText->SetPosition(Vector2f{ 7.0f, (float)AppWindow::WindowHeight - 20.0f});

	EventManager::Subscribe<OnPlayerLoseHealthEvent>(std::bind(&GameScreen::UpdateHealth, this, std::placeholders::_1));
	EventManager::Subscribe<OnScoreChangedEvent>(std::bind(&GameScreen::UpdateScore, this, std::placeholders::_1));
}

GameScreen::~GameScreen()
{
	EventManager::Unsubscribe<OnPlayerLoseHealthEvent>(std::bind(&GameScreen::UpdateHealth, this, std::placeholders::_1));
	EventManager::Unsubscribe<OnScoreChangedEvent>(std::bind(&GameScreen::UpdateScore, this, std::placeholders::_1));
}

void GameScreen::SetPlayerScore(int score)
{
	_scoreText->SetString(std::format("Score: {}", std::to_string(score)));
}

void GameScreen::SetPlayerHealth(int health, int maxHealth)
{
	_playerHealthText->SetString(std::format("Health: {}/{}", std::to_string(health), std::to_string(maxHealth)));
}

void GameScreen::UpdateHealth(const OnPlayerLoseHealthEvent& eventArg)
{
	SetPlayerHealth(eventArg.GetPlayerHealth(), eventArg.GetPlayerMaxHealth());
}

void GameScreen::UpdateScore(const OnScoreChangedEvent& eventArg)
{
	SetPlayerScore(eventArg.GetScore());
}
