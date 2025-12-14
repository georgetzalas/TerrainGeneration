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
    void FillBuffer(unsigned int, std::vector<Vertex>&, uint32_t, uint32_t) const;
private:
    GLuint VAO, VBO, EBO;
};
};
};
