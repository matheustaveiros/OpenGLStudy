#pragma once

#include <string>
#include "Renderer.h"

class Texture
{
public:

    explicit Texture(const std::string& filePath);
    ~Texture();

    // In OpenGL we have slots to bind texture, we can bind more than one texture at once
    // On Windows, on modern GPUs we generally have 32 slots
    // On mobile, we may have only 8
    // But it all depends on the current GPU. We have a function that we can call to check how many slots we have for the current GPU
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return _width; }
    inline int GetHeight() const { return _height; }

private:

    unsigned int _rendererID{ 0 };
    std::string _filePath{};
    unsigned char* _localBuffer{ nullptr };
    int _width{ 0 };
    int _height{ 0 };
    int _bytesPerPixel{ 0 };
};