#include "Logger.hpp"

namespace logger
{
Log::Log() noexcept{
}

Log::~Log()
{
}

Log& Log::Get()
{
    static Log log;
    return log;
}

void Log::SetLevel(const LogLevel& log_level)
{
    log_level_ = log_level;
}

void Log::log_warn(const std::string& logs)const
{
    std::cout << logs<< std::endl;
}

void Log::log_info(const std::string& logs) const
{
    std::cout << logs<< std::endl;

}

void Log::log_error(const std::string& logs) const
{
    std::cout << logs<< std::endl;

}

void Log::log_debug(const std::string& logs) const
{
    std::cout << logs<< std::endl;
}

void Log::log(const std::string& logs) const
{
    std::cout << logs<< std::endl;
}
} // logger