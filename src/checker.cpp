#include "checker.hpp"

#include <cmath>

#include "logger.hpp"

void Checker::CheckData(const CalculationData& data) {
    auto& log = Logger::Instance();
    log.Debug("validating input data");

    if (data.operation == Operation::OP_UNKNOWN) {
        throw std::invalid_argument("operation is not defined");
    }

    if (std::isnan(data.first_number) || std::isinf(data.first_number)) {
        throw std::invalid_argument("first number is invalid (NaN or Inf)");
    }

    if (data.operation != Operation::OP_FACT) {
        if (std::isnan(data.second_number) || std::isinf(data.second_number)) {
            throw std::invalid_argument("second number is invalid (NaN or Inf)");
        }
    }

    if (data.operation == Operation::OP_FACT) {
        if (data.first_number < 0) {
            throw std::invalid_argument("factorial defined only for non-negative numbers");
        }
        if (floor(data.first_number) != data.first_number) {
            throw std::invalid_argument("factorial defined only for integers");
        }
    }

    if (data.operation == Operation::OP_POW) {
        if (floor(data.second_number) != data.second_number) {
            throw std::invalid_argument("power exponent must be integer");
        }
    }

    log.Debug("validation passed");
}
