#pragma once
#include <glm/glm.hpp>

class Color
{
public:
	Color();

	Color(int red, int green, int blue);

	Color(int red, int green, int blue, int alpha);

	glm::vec3 getRGB();

	glm::vec4 getRGBA();

private:
	int m_Red;
	int m_Green;
	int m_Blue;
	int m_Alpha;
};
