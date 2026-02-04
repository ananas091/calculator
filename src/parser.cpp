#include "parser.hpp"

#include <getopt.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

Operation Parser::parse_operation(const std::string& op_str) {
    if (op_str == "+") return Operation::OP_ADD;
    if (op_str == "-") return Operation::OP_SUB;
    if (op_str == "*") return Operation::OP_MUL;
    if (op_str == "/") return Operation::OP_DIV;
    if (op_str == "^") return Operation::OP_POW;
    if (op_str == "!") return Operation::OP_FACT;
    return Operation::OP_UNKNOWN;
}

int Parser::parse_json(const std::string& json_str, CalculationData* data) {
    data->first_number = 0.0;
    data->second_number = 0.0;
    data->operation = Operation::OP_UNKNOWN;
    data->result = 0.0;
    data->error = mathlib::MATH_OK;

    try {
        nlohmann::json j = nlohmann::json::parse(json_str);

        if (!j.contains("operation")) {
            std::cerr << "Ошибка: отсутствует поле 'operation'\n";
            return -1;
        }

        std::string op_str = j["operation"].get<std::string>();
        data->operation = parse_operation(op_str);

        if (data->operation == Operation::OP_UNKNOWN) {
            std::cerr << "Ошибка: неизвестная операция '" << op_str << "'\n";
            std::cerr << "Доступные операции: + - * / ^ !\n";
            return -1;
        }

        if (!j.contains("operand1")) {
            std::cerr << "Ошибка: отсутствует поле 'operand1'\n";
            return -1;
        }

        if (!j["operand1"].is_number()) {
            std::cerr << "Ошибка: 'operand1' должен быть числом\n";
            return -1;
        }
        data->first_number = j["operand1"].get<double>();

        if (data->operation != Operation::OP_FACT) {
            if (!j.contains("operand2")) {
                std::cerr << "Ошибка: отсутствует поле 'operand2' для бинарной операции\n";
                return -1;
            }

            if (!j["operand2"].is_number()) {
                std::cerr << "Ошибка: 'operand2' должен быть числом\n";
                return -1;
            }
            data->second_number = j["operand2"].get<double>();
        }

        return 0;

    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Ошибка парсинга JSON: " << e.what() << "\n";
        return -1;
    } catch (const nlohmann::json::type_error& e) {
        std::cerr << "Ошибка типа JSON: " << e.what() << "\n";
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return -1;
    }
}

int Parser::parse_arguments(int argc, char* argv[], CalculationData* data) {
    if (argc < 2) {
        std::cout << "Используйте: " << argv[0] << " -h или --help для подробной информации\n";
        return -1;
    }

    if (check_help(argc, argv)) {
        return -2;
    }

    std::string json_input;

    if (argc == 2) {
        json_input = argv[1];
    } else if (argc == 3 && std::string(argv[1]) == "-f") {
        std::ifstream file(argv[2]);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл '" << argv[2] << "'\n";
            return -1;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        json_input = buffer.str();
    } else {
        std::cerr << "Ошибка: неправильное количество аргументов\n";
        std::cout << "Используйте: " << argv[0] << " -h или --help для подробной информации\n";
        return -1;
    }

    return parse_json(json_input, data);
}

int Parser::check_help(int argc, char* argv[]) {
    const char* optstring = "+hf:";

    static const struct option long_opts[] = {
        {"help", no_argument, nullptr, 'h'}, {"file", required_argument, nullptr, 'f'}, {nullptr, 0, nullptr, 0}};

    opterr = 0;
    optind = 1;

    int opt;
    while ((opt = getopt_long(argc, argv, optstring, long_opts, nullptr)) != -1) {
        if (opt == 'h') {
            return 1;
        }
    }

    optind = 1;
    return 0;
}
