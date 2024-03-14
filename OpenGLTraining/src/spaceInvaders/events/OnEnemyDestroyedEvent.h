#pragma once
#include "BaseEvent.h"
class OnEnemyDestroyedEvent : public BaseEvent
{
private:
	int _score;
public:
	explicit OnEnemyDestroyedEvent(int score);
	int GetScore() const { return _score; }
};