#pragma once

#include "mathlib.hpp"

enum class Operation { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_POW, OP_FACT, OP_UNKNOWN };

struct CalculationData {
    double first_number = 0.;
    double second_number = 0.;
    Operation operation = Operation::OP_UNKNOWN;
    double result = 0.;
    mathlib::MathError error = mathlib::MATH_OK;
};