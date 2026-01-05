#pragma once

#include <string>
#include <iostream>

enum class LogLevel{ DEBUG=0, INFO, WARNING, ERROR };

static const char* colors[4] = {"\e[0;37m", "\e[0;32m", "\e[0;33m", "\e[0;31m"};

#define RESET_COLOR "\e[0m"

namespace Core
{
    class Logger
    {
    public:
        static Logger* GetInstance();

        void Log(LogLevel, const std::string&);
        void Init();
        void Destroy();

    private:
        Logger() = default;
            
        Logger(Logger &other) = delete;
        void operator=(const Logger&) = delete;

        std::string LogToString(LogLevel);

    private:
        static Logger* logger;
    };
};