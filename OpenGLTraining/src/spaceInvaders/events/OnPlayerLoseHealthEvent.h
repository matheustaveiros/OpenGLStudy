#pragma once
#include "BaseEvent.h"
class OnPlayerLoseHealthEvent : public BaseEvent
{
private:
	int _playerHealth;
	int _maxHealth;
public:
	explicit OnPlayerLoseHealthEvent(int playerHealth, int maxHealth);
	int GetPlayerHealth() const { return _playerHealth; }
	int GetPlayerMaxHealth() const { return _maxHealth; }
};