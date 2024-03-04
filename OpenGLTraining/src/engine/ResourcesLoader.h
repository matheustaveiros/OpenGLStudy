#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "..\Texture.h"

struct TextureLoaderData
{
private:
	std::unique_ptr<Texture> _texture;
public:
	TextureLoaderData(int slot, const std::string& texturePath);
	int Slot;
	Texture* GetTexture() { return _texture.get(); }
};

class ResourcesLoader
{

private:
	/// <summary>
	/// Texture Readable Name
	/// Texture Data
	/// </summary>
	std::unordered_map<std::string, TextureLoaderData> _textureDB;
	int _slotCount = 0;


public:
	Texture* GetTexture(const std::string& textureKey, const std::string& texturePath);
};

