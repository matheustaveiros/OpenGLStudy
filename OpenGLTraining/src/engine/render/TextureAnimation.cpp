#include "TextureAnimation.h"
#include "GameTime.h"

TextureAnimation::TextureAnimation(SpriteRenderer* spriteRenderer, const std::vector<TextureLoaderData*>& textures, float animationSpeed)
	: _spriteRenderer{ spriteRenderer }, _textures{ textures }, _animationSpeed{ animationSpeed }
{
}

void TextureAnimation::Update()
{
	_animationTime += GameTime::DeltaTime * _animationSpeed;
	if (_animationTime >= 1.0f)
	{
		_animationTime = 0.0f;
		_currentIndex++;
		if (_currentIndex >= _textures.size())
		{
			_currentIndex = 0;
		}

		_spriteRenderer->SetTexture(_textures[_currentIndex]->GetTexture(), _textures[_currentIndex]->Slot);
	}
}