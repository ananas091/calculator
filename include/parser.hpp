#pragma once

#include "types.hpp"

class Parser {
public:
    Operation parse_operation(const char* op_str);
    int parse_arguments(int argc, char* argv[], CalculationData* data);
    int check_help(int argc, char* argv[]);
private:
};