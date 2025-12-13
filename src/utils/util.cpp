#include <utils/util.h> 

std::string Utils::readFileContents(const std::string& path)
{
    std::string contents = "";
    std::string line;
    std::ifstream file(path);

    if(file.good())
    {
        while(getline(file, line))
        {
            contents += line;
            contents += "\n";
        }
    }
    else
    {
        std::cout << path << " File doesnt exist" << std::endl;
    }

    file.close();

    return contents;
}

void Utils::writeFileContents(const std::string& path, const std::string& contents)
{
    std::ofstream file(path);

    if(file.good())
    {
        file << contents;
    }
    else
    {
        std::cout << path << " File doesnt exist" << std::endl;
    }

    file.close();
}

std::string Utils::getFileNameFromPath(const std::string& path)
{
    size_t pos = path.find_last_of('/') + 1;
    size_t len = path.find_last_of('.') - pos;
    return path.substr(pos, len);
}

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch(errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
