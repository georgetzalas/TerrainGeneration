#include <gfx/opengl/types/buffer.h>

Gfx::OpenGL::Buffer::Buffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

Gfx::OpenGL::Buffer::~Buffer()
{

}

void Gfx::OpenGL::Buffer::Bind() const
{
    glBindVertexArray(VAO);
}

void Gfx::OpenGL::Buffer::Unbind() const
{
    glBindVertexArray(0);
}

void Gfx::OpenGL::Buffer::FillBuffer(unsigned int size, std::vector<Vertex>& vertices, uint32_t width, uint32_t depth) const
{
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    std::vector<int> indices;

    for(int z=0; z<depth-1; z++)
    {
        for(int x=0; x<width; x++)
        {
            for(int k=0; k<2; k++)
            {
                indices.push_back(x + width * (z + k));
            }
        }
    } 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
}
