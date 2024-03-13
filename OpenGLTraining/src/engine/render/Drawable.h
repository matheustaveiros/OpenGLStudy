#pragma once
#include "Renderer.h"

class Drawable
{
public:
	virtual void Draw() = 0;

	virtual ~Drawable() = default;
};
