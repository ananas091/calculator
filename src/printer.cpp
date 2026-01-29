#include "printer.hpp"

#include <cstdio>

void Printer::print_usage(const char* program_name) {
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
    printf("%s 3 '*' 2   или   %s 3 \\* 2\n", program_name, program_name);
    printf("\n");
}

void Printer::print_result(const CalculationData* data) {
    if (data->error) {
        fprintf(stderr, "Ошибка: %s\n", mathlib::math_error_string(data->error));
        return;
    }

    printf("%.15g\n", data->result);
}