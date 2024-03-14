#pragma once
#include <glm/glm.hpp>

class Color
{
public:
	Color() = default;

	Color(float red, float green, float blue);

	Color(float red, float green, float blue, float alpha);

	glm::vec3 getRGB() const;

	glm::vec4 getRGBA() const;

private:
	float m_Red{ 1.0f };
	float m_Green{ 1.0f };
	float m_Blue{ 1.0f };
	float m_Alpha{ 1.0f };
};
