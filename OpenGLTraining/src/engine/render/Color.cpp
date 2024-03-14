#include "Color.h"

Color::Color(float red, float green, float blue)
	:m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(1)
{
}

Color::Color(float red, float green, float blue, float alpha)
	:m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(alpha)
{
}

glm::vec3 Color::getRGB() const
{
	return glm::vec3(m_Red, m_Green, m_Blue);
}

glm::vec4 Color::getRGBA() const
{
	return glm::vec4(m_Red, m_Green, m_Blue, m_Alpha);
}
