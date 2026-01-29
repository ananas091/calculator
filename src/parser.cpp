#include "parser.hpp"

#include <errno.h>
#include <getopt.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

Operation Parser::parse_operation(const char* op_str) {
    if (strcmp(op_str, "+") == 0) return Operation::OP_ADD;
    if (strcmp(op_str, "-") == 0) return Operation::OP_SUB;
    if (strcmp(op_str, "*") == 0) return Operation::OP_MUL;
    if (strcmp(op_str, "/") == 0) return Operation::OP_DIV;
    if (strcmp(op_str, "^") == 0) return Operation::OP_POW;
    if (strcmp(op_str, "!") == 0) return Operation::OP_FACT;
    return Operation::OP_UNKNOWN;
}

int Parser::parse_arguments(int argc, char* argv[], CalculationData* data) {
    data->first_number = 0.0;
    data->second_number = 0.0;
    data->operation = Operation::OP_UNKNOWN;
    data->result = 0.0;
    data->error = mathlib::MATH_OK;

    char* endptr;

    if (argc < 2) {
        printf("Используйте: %s -h или --help для подробной информации\n", argv[0]);
        return -1;
    }

    if (Parser::check_help(argc, argv)) {
        return -2;
    }

    if (argc == 3) {
        if (strcmp(argv[2], "!") == 0) {
            data->operation = Operation::OP_FACT;

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
        if (data->operation == Operation::OP_UNKNOWN) {
            fprintf(stderr, "Ошибка: неизвестная операция '%s'\n", argv[2]);
            fprintf(stderr, "Доступные операции: + - * / ^ !\n");
            return -1;
        }

        if (data->operation == Operation::OP_FACT) {
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

int Parser::check_help(int argc, char* argv[]) {
    const char* optstring = "+h";

    static const struct option long_opts[] = {{"help", no_argument, 0, 'h'}, {0, 0, 0, 0}};

    opterr = 0;
    optind = 1;

    int opt;
    while ((opt = getopt_long(argc, argv, optstring, long_opts, NULL)) != -1) {
        if (opt == 'h') {
            return 1;
        }
    }

    optind = 1;
    return 0;
}