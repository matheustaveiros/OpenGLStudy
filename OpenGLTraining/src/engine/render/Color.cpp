#include "Color.h"

Color::Color(float red, float green, float blue)
	:_red(red), _green(green), _blue(blue), _alpha(1)
{
}

Color::Color(float red, float green, float blue, float alpha)
	:_red(red), _green(green), _blue(blue), _alpha(alpha)
{
}

glm::vec3 Color::GetRGB() const
{
	return glm::vec3(_red, _green, _blue);
}

glm::vec4 Color::GetRGBA() const
{
	return glm::vec4(_red, _green, _blue, _alpha);
}
