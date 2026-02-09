#include "parser.hpp"

#include <getopt.h>

#include <format>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

#include "logger.hpp"

Operation Parser::ParseOperation(const std::string& op_str) {
    if (op_str == "+") return Operation::OP_ADD;
    if (op_str == "-") return Operation::OP_SUB;
    if (op_str == "*") return Operation::OP_MUL;
    if (op_str == "/") return Operation::OP_DIV;
    if (op_str == "^") return Operation::OP_POW;
    if (op_str == "!") return Operation::OP_FACT;
    return Operation::OP_UNKNOWN;
}

void Parser::ParseJson(const std::string& json_str, CalculationData& data) {
    data.first_number = 0.0;
    data.second_number = 0.0;
    data.operation = Operation::OP_UNKNOWN;
    data.result = 0.0;
    data.error = mathlib::MATH_OK;

    auto& log = Logger::Instance();
    log.Debug(std::format("parsing JSON: {}", json_str));

    try {
        nlohmann::json j = nlohmann::json::parse(json_str);

        if (!j.contains("operation")) {
            throw std::invalid_argument("missing field 'operation'");
        }

        std::string op_str = j["operation"].get<std::string>();
        data.operation = ParseOperation(op_str);

        if (data.operation == Operation::OP_UNKNOWN) {
            throw std::invalid_argument("unknown operation '" + op_str + "'. Available operations: + - * / ^ !");
        }

        if (!j.contains("operand1")) {
            throw std::invalid_argument("missing field 'operand1'");
        }

        if (!j["operand1"].is_number()) {
            throw std::invalid_argument("'operand1' must be a number");
        }
        data.first_number = j["operand1"].get<double>();

        if (data.operation != Operation::OP_FACT) {
            if (!j.contains("operand2")) {
                throw std::invalid_argument("missing field 'operand2' for binary operation");
            }

            if (!j["operand2"].is_number()) {
                throw std::invalid_argument("'operand2' must be a number");
            }
            data.second_number = j["operand2"].get<double>();
        }

        log.Debug(std::format("parsing successful: operand1={}, operation='{}', operand2={}", data.first_number, op_str,
                              data.second_number));

    } catch (const std::invalid_argument&) {
        throw;
    } catch (const nlohmann::json::parse_error& e) {
        throw std::invalid_argument(std::string("JSON parse error: ") + e.what());
    } catch (const nlohmann::json::type_error& e) {
        throw std::invalid_argument(std::string("JSON type error: ") + e.what());
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

void Parser::ParseArguments(int argc, char* argv[], CalculationData& data) {
    auto& log = Logger::Instance();
    log.Debug("parsing arguments");

    if (argc < 2) {
        throw std::invalid_argument(std::string("not enough arguments. Use: ") + argv[0] +
                                    " -h или --help for details");
    }

    if (CheckHelp(argc, argv)) {
        throw HelpRequestedException();
    }

    std::string json_input;

    if (argc == 2) {
        json_input = argv[1];
    } else if (argc == 3 && std::string(argv[1]) == "-f") {
        log.Debug(std::format("reading from file: {}", argv[2]));
        std::ifstream file(argv[2]);
        if (!file.is_open()) {
            throw std::runtime_error(std::string("failed to open file '") + argv[2] + "'");
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        json_input = buffer.str();
    } else {
        throw std::invalid_argument(std::string("invalid number of arguments. Use: ") + argv[0] +
                                    " -h или --help for details");
    }

    ParseJson(json_input, data);
}

bool Parser::CheckHelp(int argc, char* argv[]) {
    const char* optstring = "+hf:";

    static const struct option long_opts[] = {
        {"help", no_argument, nullptr, 'h'}, {"file", required_argument, nullptr, 'f'}, {nullptr, 0, nullptr, 0}};

    opterr = 0;
    optind = 1;

    int opt;
    while ((opt = getopt_long(argc, argv, optstring, long_opts, nullptr)) != -1) {
        if (opt == 'h') {
            return true;
        }
    }

    optind = 1;
    return false;
}
