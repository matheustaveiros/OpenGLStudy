#pragma once
#include "unordered_map"
#include <string>
#include <memory>
#include "Font.h"

class FontManager
{
private:
	static std::unordered_map<std::string, std::unique_ptr<Font>> _fontMap;
	
public:
	static void CreateFont(const std::string& key, const std::string& path, int size)
	{
		_fontMap.emplace(key, std::make_unique<Font>(path, size));
	}

	static Font* GetFont(const std::string& fontKey)
	{
		if (_fontMap.contains(fontKey))
		{
			return _fontMap[fontKey].get();
		}

		return nullptr;
	}
};

