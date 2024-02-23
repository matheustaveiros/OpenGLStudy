#pragma once
#include "Scene.h"

class GameLoop
{
private:
	std::unique_ptr<Scene> _activeScene;
	bool _isRunning = false;

public:
	void EntryPoint();
	void Loop();
};

