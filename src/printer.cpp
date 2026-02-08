#include "printer.hpp"

#include <iostream>

void Printer::PrintUsage(const std::string& program_name) {
    std::cout << "Использование: " << program_name << " '<json>'\n"
              << "          или: " << program_name << " -f <файл.json>\n"
              << "\n"
              << "Формат JSON:\n"
              << "  Бинарные операции: {\"operand1\": <число>, \"operation\": \"<оп>\", \"operand2\": <число>}\n"
              << "  Факториал:         {\"operand1\": <число>, \"operation\": \"!\"}\n"
              << "\n"
              << "Операции:\n"
              << "  +    Сложение\n"
              << "  -    Вычитание\n"
              << "  *    Умножение\n"
              << "  /    Деление\n"
              << "  ^    Возведение в степень\n"
              << "  !    Факториал\n"
              << "\n"
              << "Примеры:\n"
              << "  " << program_name << " '{\"operand1\": 10, \"operation\": \"+\", \"operand2\": 5}'\n"
              << "  " << program_name << " '{\"operand1\": 5, \"operation\": \"!\"}'\n"
              << "  " << program_name << " -f input.json\n"
              << "\n";
}

void Printer::PrintResult(const CalculationData& data) {
    if (data.error == mathlib::MATH_OK)
        std::cout << data.result << "\n";
    else
        std::cout << "Ошибка: " << mathlib::math_error_string(data.error) << "\n";
}

void Printer::PrintError(const std::string& message) { std::cerr << "Ошибка: " << message << "\n"; }
