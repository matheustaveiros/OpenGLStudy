#pragma once
#include "render/Text.h"
#include "Screen.h"
#include "events/OnPlayerLoseHealthEvent.h"
#include "events/OnEnemyDestroyedEvent.h"

class GameScreen : public Screen
{
private:
	Text* _scoreText;
	Text* _playerHealthText;
public:
	explicit GameScreen(Guid guid);
	~GameScreen();
	void SetPlayerScore(int score);
	void SetPlayerHealth(int health, int maxHealth);
	void UpdateHealth(const OnPlayerLoseHealthEvent& eventArg);
	void UpdateScore(const OnEnemyDestroyedEvent& eventArg);
};

