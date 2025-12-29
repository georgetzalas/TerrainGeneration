#include "texture.h"

Gfx::OpenGL::Texture::Texture(uint32_t width, uint32_t height, float* data)
{
    this->width  = width;
    this->height = height;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
   
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_FLOAT, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
}

Gfx::OpenGL::Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Gfx::OpenGL::Texture::Bind(uint32_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Gfx::OpenGL::Texture::Unbind(uint32_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::string Gfx::OpenGL::Texture::GetName()
{
	return this->name;
}

GLuint Gfx::OpenGL::Texture::GetID()
{
    return id;
}