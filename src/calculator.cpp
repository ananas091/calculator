#include "calculator.hpp"

void Calculator::calculate(CalculationData* data) {
    mathlib::MathError err = mathlib::MATH_OK;

    switch (data->operation) {
        case Operation::OP_ADD:
            err = mathlib::math_add(data->first_number, data->second_number, &data->result);
            break;

        case Operation::OP_SUB:
            err = mathlib::math_sub(data->first_number, data->second_number, &data->result);
            break;

        case Operation::OP_MUL:
            err = mathlib::math_mul(data->first_number, data->second_number, &data->result);
            break;

        case Operation::OP_DIV:
            err = mathlib::math_div(data->first_number, data->second_number, &data->result);
            break;

        case Operation::OP_POW:
            err = mathlib::math_pow(data->first_number, data->second_number, &data->result);
            break;

        case Operation::OP_FACT:
            err = mathlib::math_factorial(data->first_number, &data->result);
            break;

        default:
            err = mathlib::MATH_ERR_INVALID_ARG;
            break;
    }

    data->error = err;
}