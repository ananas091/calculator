#include "printer.hpp"

#include <iostream>

void Printer::PrintUsage(const std::string& program_name) {
    std::cout << "Usage: " << program_name << " '<json>'\n"
              << "   or: " << program_name << " -f <file.json>\n"
              << "\n"
              << "JSON format:\n"
              << "  Binary operations: {\"operand1\": <number>, \"operation\": \"<op>\", \"operand2\": <number>}\n"
              << "  Factorial:         {\"operand1\": <number>, \"operation\": \"!\"}\n"
              << "\n"
              << "Operations:\n"
              << "  +    Addition\n"
              << "  -    Subtraction\n"
              << "  *    Multiplication\n"
              << "  /    Division\n"
              << "  ^    Power\n"
              << "  !    Factorial\n"
              << "\n"
              << "Examples:\n"
              << "  " << program_name << " '{\"operand1\": 10, \"operation\": \"+\", \"operand2\": 5}'\n"
              << "  " << program_name << " '{\"operand1\": 5, \"operation\": \"!\"}'\n"
              << "  " << program_name << " -f input.json\n"
              << "\n";
}

void Printer::PrintResult(const CalculationData& data) {
    if (data.error == mathlib::MATH_OK)
        std::cout << data.result << "\n";
    else
        std::cout << "Error: " << mathlib::math_error_string(data.error) << "\n";
}

void Printer::PrintError(const std::string& message) { std::cerr << "Error: " << message << "\n"; }
