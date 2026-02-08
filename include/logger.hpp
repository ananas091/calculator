#pragma once

#include <memory>
#include <spdlog/spdlog.h>

class Logger {
public:
    static Logger& Instance() {
        static Logger self;
        return self;
    }

    std::shared_ptr<spdlog::logger>& Get() { return _logger; }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();
    std::shared_ptr<spdlog::logger> _logger;
};
