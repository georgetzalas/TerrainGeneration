#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/util.h>

class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use();

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setMatrix44f(const std::string& name, glm::mat4 value);
    void setVec2f(const std::string& name, float x, float y);
    void setVec2f(const std::string& name, glm::vec2 value);
    void setVec3f(const std::string& name, float x, float y, float z);
    void setVec3f(const std::string& name, glm::vec3 value);
    void setVec4f(const std::string& name, float x, float y, float z, float w);
    void setVec4f(const std::string& name, glm::vec4 value);

	std::string getVertexPath();
	std::string getFragmentPath();

	std::string getName();

private:
    GLuint id;
	std::string name;
    std::string vertexPath;
    std::string fragmentPath;
	
    
    void compileShader();
};
