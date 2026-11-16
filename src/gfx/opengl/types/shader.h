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

    void Use() const;

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMatrix44f(const std::string& name, glm::mat4 value) const;
    void SetVec2f(const std::string& name, float x, float y) const;
    void SetVec2f(const std::string& name, glm::vec2 value) const;
    void SetVec3f(const std::string& name, float x, float y, float z) const;
    void SetVec3f(const std::string& name, glm::vec3 value) const;
    void SetVec4f(const std::string& name, float x, float y, float z, float w) const;
    void SetVec4f(const std::string& name, glm::vec4 value) const;

	const std::string& GetVertexPath() const;
	const std::string& GetFragmentPath() const;

	const std::string& GetName() const;

private:
    void CompileShader();

private:
    GLuint id;
	std::string name;
    std::string vertexPath;
    std::string fragmentPath;
};
};
};
