#pragma once
#include "Screen.h"
#include "unordered_map"
#include "Scene.h"

class ScreenManager
{
private:
	static std::unordered_map<std::string, Screen*> _screens;
public:

	template<typename T, typename = std::enable_if_t<std::is_base_of_v<Screen, T>>>
	static T* CreateScreen(const std::string& screenKey)
	{
		T* newScreen = Scene::ActiveScene->InstantiateGameObject<T>();
		dynamic_cast<Screen*>(newScreen)->SetKey(screenKey);
		_screens.emplace(screenKey, newScreen);
		return newScreen;
	}

	template<typename T, typename = std::enable_if_t<std::is_base_of_v<Screen, T>>>
	static T* GetScreen(const std::string& screenKey)
	{
		if (_screens.contains(screenKey))
		{
			return _screens[screenKey];
		}

		return nullptr;
	}

	static void DestroyScreen(const std::string& screenKey)
	{
		Scene::ActiveScene->DestroyGameObject(_screens[screenKey]->GetGuid());
		_screens.erase(screenKey);
	}
};