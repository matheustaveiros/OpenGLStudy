#pragma once

class IndexBuffer
{
public:
    // Size = bytes
    // Count = elements count
    IndexBuffer(const unsigned int* Data, unsigned int Count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return _count; }

private:

    // Stores the ID that represents this object on OpenGL side (can be a vertex buffer, vertex array, a texture, shader...)).
    // This ID approach is also used on other graphic APIs, such DirectX, that's why a generic name is used here
    unsigned int _rendererID;
    unsigned int _count; // How many indexes it has
};