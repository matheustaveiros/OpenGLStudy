#pragma once
#include <glm/glm.hpp>

class Color
{
public:
	Color() = default;

	Color(float red, float green, float blue);

	Color(float red, float green, float blue, float alpha);

	glm::vec3 GetRGB() const;

	glm::vec4 GetRGBA() const;

private:
	float _red{ 1.0f };
	float _green{ 1.0f };
	float _blue{ 1.0f };
	float _alpha{ 1.0f };
};
