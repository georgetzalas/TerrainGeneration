#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>
#include <iostream>

namespace Gfx
{
namespace OpenGL
{
class Texture
{
public:
	Texture(std::string path);
	~Texture();

	void Bind(uint32_t unit = 0);
	void Unbind(uint32_t unit = 0);

	std::string GetName();
    GLuint GetID();

private:
	int width;
	int height;
	int channels;
	std::string name;
	GLuint id;
};
};
};