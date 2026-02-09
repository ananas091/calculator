#pragma once

#include <memory>
#include <spdlog/spdlog.h>

class Logger {
public:
    static Logger& Instance() {
        static Logger self;
        return self;
    }

    void Debug(const std::string& msg);
    void Info(const std::string& msg);
    void Error(const std::string& msg);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();
    std::shared_ptr<spdlog::logger> _logger;
};
