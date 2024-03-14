#pragma once
#include <string>
#include <map>
#include <glm/glm.hpp>

struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

class Font
{
public:
    Font(const std::string& file, unsigned int fontSize);

    std::map<char, Character> GetCharacters();

private:
	std::map<char, Character> _characters;
    void LoadFromFile(const std::string& file, unsigned int fontSize);
};
