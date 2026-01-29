#include "checker.hpp"

#include <cmath>
#include <cstdio>

int Checker::check_data(const CalculationData* data) {
    if (data->operation == Operation::OP_UNKNOWN) {
        fprintf(stderr, "Ошибка: операция не определена\n");
        return -1;
    }

    if (std::isnan(data->first_number) || std::isinf(data->first_number)) {
        fprintf(stderr, "Ошибка: первое число некорректно (NaN или Inf)\n");
        return -1;
    }

    if (data->operation != Operation::OP_FACT) {
        if (std::isnan(data->second_number) || std::isinf(data->second_number)) {
            fprintf(stderr, "Ошибка: второе число некорректно (NaN или Inf)\n");
            return -1;
        }
    }

    if (data->operation == Operation::OP_FACT) {
        if (data->first_number < 0) {
            fprintf(stderr, "Ошибка: факториал определён только для неотрицательных чисел\n");
            return -1;
        }
        if (floor(data->first_number) != data->first_number) {
            fprintf(stderr, "Ошибка: факториал определён только для целых чисел\n");
            return -1;
        }
    }

    if (data->operation == Operation::OP_POW) {
        if (floor(data->second_number) != data->second_number) {
            fprintf(stderr, "Ошибка: показатель степени должен быть целым числом\n");
            return -1;
        }
    }

    return 0;
}