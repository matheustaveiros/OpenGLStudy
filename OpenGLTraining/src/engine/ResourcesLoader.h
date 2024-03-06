#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "../Texture.h"

struct TextureLoaderData
{
private:
	std::unique_ptr<Texture> _texture;
public:
	TextureLoaderData() { Slot = 0; }

	TextureLoaderData(unsigned int slot, const std::string& texturePath)
	{
		Slot = slot;
		_texture = std::make_unique<Texture>(texturePath);
	}

	unsigned int Slot;
	Texture* GetTexture() { return _texture.get(); }
};

class ResourcesLoader
{

private:
	/// <summary>
	/// Texture Readable Name
	/// Texture Data
	/// </summary>
	inline static std::unordered_map<std::string, TextureLoaderData> _textureDB;
	inline static unsigned int _slotCount;


public:
	static TextureLoaderData& GetTexture(const std::string& textureKey, const std::string& texturePath)
	{
		if (_textureDB.contains(textureKey))
		{
			return _textureDB[textureKey];
		}

		_textureDB.emplace(textureKey, TextureLoaderData(_slotCount, texturePath));
		_slotCount++;

		return _textureDB[textureKey];
	}
};

