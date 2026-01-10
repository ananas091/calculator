#include <iostream>
#include <stdexcept>
#include <string>

#include "mathlib.h"

static void PrintHelp(const std::string& prog) {
    std::cout << "Usage:\n"
              << "  " << prog << " <a> <op> <b>\n"
              << "  " << prog << " <base> ^ <exp_int>\n"
              << "  " << prog << " <n> !\n"
              << "  " << prog << " -h | --help\n\n"
              << "Operations:\n"
              << "  +  -  '*'  /\n"
              << "  ^  (power, exponent is integer, iterative)\n"
              << "  !  (factorial, recursive)\n\n"
              << "Examples:\n"
              << "  " << prog << " 2 + 3\n"
              << "  " << prog << " 10 / 2\n"
              << "  " << prog << " 2 ^ 10\n"
              << "  " << prog << " 5 !\n";
}

static void PrintUsageError(const std::string& prog, const std::string& error = "") {
    if (!error.empty()) {
        std::cerr << "Error: " << error << "\n";
    }
    std::cerr << "Run '" << prog << " --help' for usage information.\n";
}

int main(int argc, char** argv) {
    const std::string prog = (argc > 0 && argv && argv[0]) ? argv[0] : "calculator";

    if (argc < 2) {
        PrintUsageError(prog);
        return 1;
    }

    const std::string arg1 = argv[1];
    if (arg1 == "-h" || arg1 == "--help") {
        PrintHelp(prog);
        return 0;
    }

    try {
        // Factorial: "n !"
        if (argc == 3 && std::string(argv[2]) == "!") {
            const unsigned long long n = std::stoull(argv[1]);
            std::cout << mathlib::factorial(n) << "\n";
            return 0;
        }

        // Binary ops: "a op b"
        if (argc != 4) {
            PrintUsageError(prog, "expected 3 arguments");
            return 1;
        }

        const double a = std::stod(argv[1]);
        const std::string op = argv[2];

        if (op == "^") {
            const long long exp = std::stoll(argv[3]);
            std::cout << mathlib::pow(a, exp) << "\n";
            return 0;
        }

        const double b = std::stod(argv[3]);

        if (op == "+") {
            std::cout << mathlib::add(a, b) << "\n";
        } else if (op == "-") {
            std::cout << mathlib::sub(a, b) << "\n";
        } else if (op == "*") {
            std::cout << mathlib::mul(a, b) << "\n";
        } else if (op == "/") {
            std::cout << mathlib::div(a, b) << "\n";
        } else {
            PrintUsageError(prog, "unknown operator: " + op);
            return 1;
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }
}
