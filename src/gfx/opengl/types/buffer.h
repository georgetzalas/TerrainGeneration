#pragma once

#include <vector>
#include <glad/glad.h>
#include <utils/types.h>

namespace Gfx
{
namespace OpenGL
{
class Buffer
{
public:
    Buffer();
    ~Buffer();

    void Bind() const;
    void Unbind() const;
    void FillBuffer(unsigned int, std::vector<Vertex>&, uint32_t, uint32_t);
    uint32_t GetNumberStrips() const;
    uint32_t GetVerticesPerStrip() const;

private:
    GLuint VAO, VBO, EBO;
    uint32_t width;
    uint32_t depth;
};
};
};
