#include "ResourcesLoader.h"

TextureLoaderData::TextureLoaderData(int slot, const std::string& texturePath)
{
	Slot = slot;
	_texture = std::make_unique<Texture>(texturePath);
}

Texture* ResourcesLoader::GetTexture(const std::string& textureKey, const std::string& texturePath)
{
	if (_textureDB.contains(textureKey))
	{
		return _textureDB[textureKey].GetTexture();
	}
	
	_textureDB.emplace(textureKey, TextureLoaderData{ _slotCount, texturePath });
	_slotCount++;

	return _textureDB[textureKey].GetTexture();
}
