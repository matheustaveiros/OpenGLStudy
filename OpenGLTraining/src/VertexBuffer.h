#pragma once

/// \\brief Creates a Vertex Buffer using the Data and Size passed
/// with functions to bind it as current, unbind
/// It also deletes the buffer when instance is destroyed

class VertexBuffer
{
public:
    VertexBuffer(const void* Data, unsigned int Size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:

    // Stores the ID that represents this object on OpenGL side (can be a vertex buffer, vertex array, a texture, shader...)).
    // This ID approach is also used on other graphic APIs, such DirectX, that's why a generic name is used here
    unsigned int m_RendererID;
};