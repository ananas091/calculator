#include "logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>

Logger::Logger() {
    _logger = spdlog::basic_logger_mt("calculator", "/tmp/calculator.log", true);
    _logger->set_level(spdlog::level::debug);
    _logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
}
