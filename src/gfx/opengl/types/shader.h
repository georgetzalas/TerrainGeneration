#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/util.h>

namespace Gfx
{
namespace OpenGL
{
class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Use();

    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetMatrix44f(const std::string& name, glm::mat4 value);
    void SetVec2f(const std::string& name, float x, float y);
    void SetVec2f(const std::string& name, glm::vec2 value);
    void SetVec3f(const std::string& name, float x, float y, float z);
    void SetVec3f(const std::string& name, glm::vec3 value);
    void SetVec4f(const std::string& name, float x, float y, float z, float w);
    void SetVec4f(const std::string& name, glm::vec4 value);

	std::string GetVertexPath();
	std::string GetFragmentPath();

	std::string GetName();

private:
    GLuint id;
	std::string name;
    std::string vertexPath;
    std::string fragmentPath;
	
    
    void CompileShader();
};
};
};
