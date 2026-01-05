#include <core/logger.h>

Core::Logger* Core::Logger::logger = nullptr;

Core::Logger* Core::Logger::GetInstance()
{
    if(logger= nullptr)
        logger = new Logger();
    return logger;
}

void Core::Logger::Log(LogLevel level, const std::string& message)
{
    std::cout << colors[(int)level] << LogToString(level) << " " << message <<  RESET_COLOR << std::endl;
}

std::string Core::Logger::LogToString(LogLevel level)
{
    switch(level)
    {
        case LogLevel::DEBUG:
            return "[DEBUG]";
        case LogLevel::INFO:
            return "[INFO]";
        case LogLevel::WARNING:
            return "[WARNING]";
        case LogLevel::ERROR:
            return "[ERROR]";
        default:
            return "Unknown log level";
    };
}

void Core::Logger::Init()
{
    logger->Log(LogLevel::INFO, "Initialized Logger System");
}

void Core::Logger::Destroy()
{
    logger->Log(LogLevel::INFO, "Destroyed Logger System");
    delete logger;
}