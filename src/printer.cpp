#include "printer.hpp"

#include <cstdio>

void Printer::print_usage(const char* program_name) {
    printf("Использование: %s '<json>'\n", program_name);
    printf("          или: %s -f <файл.json>\n", program_name);
    printf("\n");
    printf("Формат JSON:\n");
    printf("  Бинарные операции: {\"operand1\": <число>, \"operation\": \"<оп>\", \"operand2\": <число>}\n");
    printf("  Факториал:         {\"operand1\": <число>, \"operation\": \"!\"}\n");
    printf("\n");
    printf("Операции:\n");
    printf("  +    Сложение\n");
    printf("  -    Вычитание\n");
    printf("  *    Умножение\n");
    printf("  /    Деление\n");
    printf("  ^    Возведение в степень\n");
    printf("  !    Факториал\n");
    printf("\n");
    printf("Примеры:\n");
    printf("  %s '{\"operand1\": 10, \"operation\": \"+\", \"operand2\": 5}'\n", program_name);
    printf("  %s '{\"operand1\": 5, \"operation\": \"!\"}'\n", program_name);
    printf("  %s -f input.json\n", program_name);
    printf("\n");
}

void Printer::print_result(const CalculationData* data) {
    if (data->error) {
        fprintf(stderr, "Ошибка: %s\n", mathlib::math_error_string(data->error));
        return;
    }

    printf("%.15g\n", data->result);
}