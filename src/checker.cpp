#include "checker.hpp"

#include <cmath>

void Checker::CheckData(const CalculationData& data) {
    if (data.operation == Operation::OP_UNKNOWN) {
        throw std::invalid_argument("операция не определена");
    }

    if (std::isnan(data.first_number) || std::isinf(data.first_number)) {
        throw std::invalid_argument("первое число некорректно (NaN или Inf)");
    }

    if (data.operation != Operation::OP_FACT) {
        if (std::isnan(data.second_number) || std::isinf(data.second_number)) {
            throw std::invalid_argument("второе число некорректно (NaN или Inf)");
        }
    }

    if (data.operation == Operation::OP_FACT) {
        if (data.first_number < 0) {
            throw std::invalid_argument("факториал определён только для неотрицательных чисел");
        }
        if (floor(data.first_number) != data.first_number) {
            throw std::invalid_argument("факториал определён только для целых чисел");
        }
    }

    if (data.operation == Operation::OP_POW) {
        if (floor(data.second_number) != data.second_number) {
            throw std::invalid_argument("показатель степени должен быть целым числом");
        }
    }
}
