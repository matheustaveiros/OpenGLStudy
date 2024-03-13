#pragma once
#include "render/Text.h"
#include "Screen.h"

class GameScreen : public Screen
{
private:
	Text* _scoreText;
	Text* _playerHealthText;
public:
	GameScreen(Guid guid);
	void SetPlayerScore(int score);
	void SetPlayerHealth(int health, int maxHealth);
};

