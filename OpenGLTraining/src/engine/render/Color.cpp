#include "Color.h"

Color::Color()
	:m_Red(1), m_Green(1), m_Blue(1), m_Alpha(1)
{
}

Color::Color(int red, int green, int blue)
	:m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(1)
{
}

Color::Color(int red, int green, int blue, int alpha)
	:m_Red(red), m_Green(green), m_Blue(blue), m_Alpha(alpha)
{
}

glm::vec3 Color::getRGB()
{
	return glm::vec3(m_Red, m_Green, m_Blue);
}

glm::vec4 Color::getRGBA()
{
	return glm::vec4(m_Red, m_Green, m_Blue, m_Alpha);
}
