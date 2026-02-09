#include "logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>

void Logger::Debug(const std::string& msg) { _logger->debug(msg); }
void Logger::Info(const std::string& msg) { _logger->info(msg); }
void Logger::Error(const std::string& msg) { _logger->error(msg); }

Logger::Logger() {
    _logger = spdlog::basic_logger_mt("calculator", "/tmp/calculator.log", true);
    _logger->set_level(spdlog::level::debug);
    _logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
}
