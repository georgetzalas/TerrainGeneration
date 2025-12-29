#include <gfx/opengl/types/texture.h>

Gfx::OpenGL::Texture::Texture(std::string path)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if(channels == 3) //JPG
	{
		if(data)
		{
            GLenum internalFormat = GL_RGB; 

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "Failed to load texture" << std::endl;
		}
	}else if(channels == 4) //PNG
	{
		if(data)
		{
            GLenum internalFormat = GL_RGBA; 

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "Failed to load texture" << std::endl;
		}
	}
	else if(channels == 2)
	{
		if(data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "Failed to load texture" << std::endl;
		}
	}
	else if(channels == 1)
	{
		if(data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "Failed to load texture" << std::endl;
		}
	}
	else
	{
		std::cerr << "Not valid image(png/jpeg) " << path << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
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