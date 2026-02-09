#include "calculator.hpp"

#include <format>

#include "logger.hpp"

void Calculator::Calculate(CalculationData& data) {
    auto& log = Logger::Instance();
    log.Debug("start calculation");

    switch (data.operation) {
        case Operation::OP_ADD:
            data.error = mathlib::math_add(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_SUB:
            data.error = mathlib::math_sub(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_MUL:
            data.error = mathlib::math_mul(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_DIV:
            data.error = mathlib::math_div(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_POW:
            data.error = mathlib::math_pow(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_FACT:
            data.error = mathlib::math_factorial(data.first_number, &data.result);
            break;

        default:
            throw std::invalid_argument("unknown operation");
    }

    if (data.error != mathlib::MATH_OK) throw std::runtime_error(mathlib::math_error_string(data.error));

    log.Debug(std::format("result: {}", data.result));
}
