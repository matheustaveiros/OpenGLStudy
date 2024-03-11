#pragma once

#include <vector>
#include "Texture.h"
#include "ResourcesLoader.h"
#include "SpriteRenderer.h"

class TextureAnimation
{
private:
	SpriteRenderer* _spriteRenderer;
	std::vector<TextureLoaderData*> _textures;
	int _currentIndex{ 0 };

	float _animationSpeed{ 0.0f };
	float _animationTime{ 0.0f };

public:
	TextureAnimation() = default;
	TextureAnimation(SpriteRenderer* spriteRenderer, const std::vector<TextureLoaderData*>& textures, float animationSpeed = 1.0f);
	void Update();
};