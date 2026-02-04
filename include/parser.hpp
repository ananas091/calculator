#pragma once

#include <string>

#include "types.hpp"

class Parser {
public:
    Operation parse_operation(const std::string& op_str);
    int parse_json(const std::string& json_str, CalculationData* data);
    int parse_arguments(int argc, char* argv[], CalculationData* data);
    int check_help(int argc, char* argv[]);
private:
};