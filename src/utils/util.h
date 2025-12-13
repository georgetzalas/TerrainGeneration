#pragma once
 
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef WIN32
#include <unistd.h>
#endif
 
#ifdef WIN32
#define stat _stat
#endif

#include <string>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Utils
{
    std::string readFileContents(const std::string&);
    void writeFileContents(const std::string&, const std::string&);
    std::string getFileNameFromPath(const std::string&);
};

GLenum glCheckError_(const char*, int);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

