#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <utils/util.h>

namespace Gfx
{
namespace OpenGL
{
class Texture
{
public:
	Texture(std::string path);
	Texture();
	~Texture();

	void Bind(uint32_t unit = 0);
	void Unbind(uint32_t unit = 0);

	void LoadData(uint32_t width, uint32_t height, u_char* data);

	std::string GetName();
    GLuint GetID();

	glm::vec3 GetColor(int x, int y);

private:
	int width;
	int height;
	int channels;
	unsigned char* data;
	std::string name;
	GLuint id;
};
};
};