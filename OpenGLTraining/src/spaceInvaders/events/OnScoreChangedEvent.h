#pragma once
#include "BaseEvent.h"
class OnScoreChangedEvent : public BaseEvent
{
private:
	int _score;
public:
	OnScoreChangedEvent(int score);
	int GetScore() const { return _score; }
};