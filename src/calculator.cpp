#include "calculator.hpp"

void Calculator::Calculate(CalculationData& data) {
    switch (data.operation) {
        case Operation::OP_ADD:
            mathlib::math_add(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_SUB:
            mathlib::math_sub(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_MUL:
            mathlib::math_mul(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_DIV:
            mathlib::math_div(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_POW:
            mathlib::math_pow(data.first_number, data.second_number, &data.result);
            break;

        case Operation::OP_FACT:
            mathlib::math_factorial(data.first_number, &data.result);
            break;

        default:
            throw std::invalid_argument("неизвестная операция");
    }
}
