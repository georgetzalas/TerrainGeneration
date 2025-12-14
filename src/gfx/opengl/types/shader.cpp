#include <gfx/opengl/types/shader.h>

Gfx::OpenGL::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	this->name = Utils::getFileNameFromPath(vertexPath);

	this->vertexPath = vertexPath; 
	this->fragmentPath = fragmentPath; 

	CompileShader();
}

Gfx::OpenGL::Shader::~Shader()
{
    glDeleteShader(id);
}

void Gfx::OpenGL::Shader::Use()
{
    glUseProgram(id);
}

void Gfx::OpenGL::Shader::CompileShader()
{
    int  success;
    char infoLog[512];

    std::string vertexCode = Utils::readFileContents(vertexPath);
    std::string fragmentCode = Utils::readFileContents(fragmentPath);

    //VERTEX//

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexCCode = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &vertexCCode, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //FRAGMENT//
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentCCode = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentCCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Gfx::OpenGL::Shader::SetBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Gfx::OpenGL::Shader::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Gfx::OpenGL::Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Gfx::OpenGL::Shader::SetMatrix44f(const std::string& name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Gfx::OpenGL::Shader::SetVec2f(const std::string& name, float x, float y)
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void Gfx::OpenGL::Shader::SetVec2f(const std::string& name, glm::vec2 value)
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Gfx::OpenGL::Shader::SetVec3f(const std::string& name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Gfx::OpenGL::Shader::SetVec3f(const std::string& name, glm::vec3 value)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Gfx::OpenGL::Shader::SetVec4f(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void Gfx::OpenGL::Shader::SetVec4f(const std::string& name, glm::vec4 value)
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

std::string Gfx::OpenGL::Shader::GetName()
{
	return this->name;
}

std::string Gfx::OpenGL::Shader::GetVertexPath()
{
	return vertexPath;
}

std::string Gfx::OpenGL::Shader::GetFragmentPath()
{
	return fragmentPath;
}
