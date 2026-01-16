#include <errno.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mathlib.hpp"

typedef enum { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_POW, OP_FACT, OP_UNKNOWN } Operation;

typedef struct {
    double first_number;
    double second_number;
    Operation operation;
    double result;
    MathError error;
} CalculationData;

void print_usage(const char* program_name) {
    printf("Использование: %s <число1> <операция> <число2>\n", program_name);
    printf("          или: %s <число> !\n", program_name);
    printf("\n");
    printf("Операции:\n");
    printf("  +    Сложение\n");
    printf("  -    Вычитание\n");
    printf("  *    Умножение\n");
    printf("  /    Деление\n");
    printf("  ^    Возведение в степень\n");
    printf("  !    Факториал\n");
    printf("\n");
    printf("Примечание: в bash символ * нужно экранировать:\n");
    printf("  %s 3 '*' 2   или   %s 3 \\* 2\n", program_name, program_name);
    printf("\n");
}

static int check_help(int argc, char* argv[]) {
    const char* optstring = "+h";

    static const struct option long_opts[] = {{"help", no_argument, 0, 'h'}, {0, 0, 0, 0}};

    opterr = 0;
    optind = 1;

    int opt;
    while ((opt = getopt_long(argc, argv, optstring, long_opts, NULL)) != -1) {
        if (opt == 'h') {
            print_usage(argv[0]);
            return 1;
        }
    }

    optind = 1;
    return 0;
}

void print_result(const CalculationData* data) {
    if (data->error) {
        fprintf(stderr, "Ошибка: %s\n", math_error_string(data->error));
        return;
    }

    printf("%.15g\n", data->result);
}

Operation parse_operation(const char* op_str) {
    if (strcmp(op_str, "+") == 0) return OP_ADD;
    if (strcmp(op_str, "-") == 0) return OP_SUB;
    if (strcmp(op_str, "*") == 0) return OP_MUL;
    if (strcmp(op_str, "/") == 0) return OP_DIV;
    if (strcmp(op_str, "^") == 0) return OP_POW;
    if (strcmp(op_str, "!") == 0) return OP_FACT;
    return OP_UNKNOWN;
}

int parse_arguments(int argc, char* argv[], CalculationData* data) {
    data->first_number = 0.0;
    data->second_number = 0.0;
    data->operation = OP_UNKNOWN;
    data->result = 0.0;
    data->error = MATH_OK;

    char* endptr;

    if (argc < 2) {
        printf("Используйте: %s -h или --help для подробной информации\n", argv[0]);
        return -1;
    }

    if (check_help(argc, argv)) {
        return 0;
    }

    if (argc == 3) {
        if (strcmp(argv[2], "!") == 0) {
            data->operation = OP_FACT;

            errno = 0;
            data->first_number = strtod(argv[1], &endptr);
            if (errno != 0 || *endptr != '\0') {
                fprintf(stderr, "Ошибка: некорректное число '%s'\n", argv[1]);
                return -1;
            }

            data->second_number = 0.0;
            return 0;
        } else {
            fprintf(stderr, "Ошибка: для унарной операции ожидается '!'\n");
            return -1;
        }
    }

    if (argc == 4) {
        errno = 0;
        data->first_number = strtod(argv[1], &endptr);
        if (errno != 0 || *endptr != '\0') {
            fprintf(stderr, "Ошибка: некорректное первое число '%s'\n", argv[1]);
            return -1;
        }

        data->operation = parse_operation(argv[2]);
        if (data->operation == OP_UNKNOWN) {
            fprintf(stderr, "Ошибка: неизвестная операция '%s'\n", argv[2]);
            fprintf(stderr, "Доступные операции: + - * / ^ !\n");
            return -1;
        }

        if (data->operation == OP_FACT) {
            fprintf(stderr, "Ошибка: факториал - унарная операция\n");
            fprintf(stderr, "Используйте: %s <число> !\n", argv[0]);
            return -1;
        }

        errno = 0;
        data->second_number = strtod(argv[3], &endptr);
        if (errno != 0 || *endptr != '\0') {
            fprintf(stderr, "Ошибка: некорректное второе число '%s'\n", argv[3]);
            return -1;
        }

        return 0;
    }

    fprintf(stderr, "Ошибка: неправильное количество аргументов\n");
    printf("Используйте: %s -h или --help для подробной информации\n", argv[0]);
    return -1;
}

int check_data(const CalculationData* data) {
    if (data->operation == OP_UNKNOWN) {
        fprintf(stderr, "Ошибка: операция не определена\n");
        return -1;
    }

    if (isnan(data->first_number) || isinf(data->first_number)) {
        fprintf(stderr, "Ошибка: первое число некорректно (NaN или Inf)\n");
        return -1;
    }

    if (data->operation != OP_FACT) {
        if (isnan(data->second_number) || isinf(data->second_number)) {
            fprintf(stderr, "Ошибка: второе число некорректно (NaN или Inf)\n");
            return -1;
        }
    }

    if (data->operation == OP_FACT) {
        if (data->first_number < 0) {
            fprintf(stderr, "Ошибка: факториал определён только для неотрицательных чисел\n");
            return -1;
        }
        if (floor(data->first_number) != data->first_number) {
            fprintf(stderr, "Ошибка: факториал определён только для целых чисел\n");
            return -1;
        }
    }

    if (data->operation == OP_POW) {
        if (floor(data->second_number) != data->second_number) {
            fprintf(stderr, "Ошибка: показатель степени должен быть целым числом\n");
            return -1;
        }
    }

    return 0;
}

void calculate(CalculationData* data) {
    MathError err = MATH_OK;

    switch (data->operation) {
        case OP_ADD:
            err = math_add(data->first_number, data->second_number, &data->result);
            break;

        case OP_SUB:
            err = math_sub(data->first_number, data->second_number, &data->result);
            break;

        case OP_MUL:
            err = math_mul(data->first_number, data->second_number, &data->result);
            break;

        case OP_DIV:
            err = math_div(data->first_number, data->second_number, &data->result);
            break;

        case OP_POW:
            err = math_pow(data->first_number, data->second_number, &data->result);
            break;

        case OP_FACT:
            err = math_factorial(data->first_number, &data->result);
            break;

        default:
            err = MATH_ERR_INVALID_ARG;
            break;
    }

    data->error = err;
}

int run(int argc, char* argv[]) {
    CalculationData data;

    if (parse_arguments(argc, argv, &data) < 0) {
        return 1;
    }

    if (check_data(&data) < 0) {
        return 1;
    }

    calculate(&data);
    print_result(&data);

    return data.error ? 1 : 0;
}

int main(int argc, char* argv[]) { return run(argc, argv); }
