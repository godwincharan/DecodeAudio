#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

namespace logger
{
enum class LogLevel
{
    WARN = 0x01,
    INFO = 0x02,
    ERROR = 0x04,
    DEBUG = 0x07
};

class Log final
{
private:
    LogLevel log_level_{LogLevel::DEBUG};
private:
    explicit Log() noexcept;
    ~Log();
public:
    static Log& Get();
    void SetLevel(const LogLevel& log_level);
    
    void log_warn(const std::string& logs)const;
    void log_info(const std::string& logs) const;
    void log_error(const std::string& logs) const;
    void log_debug(const std::string& logs) const;
    void log(const std::string& logs) const;
};
} // logger
#endif //LOGGER_HPP

