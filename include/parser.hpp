#pragma once

#include <string>

#include "types.hpp"

class Parser {
public:
    Operation ParseOperation(const std::string& op_str);
    void ParseJson(const std::string& json_str, CalculationData& data);
    void ParseArguments(int argc, char* argv[], CalculationData& data);
    bool CheckHelp(int argc, char* argv[]);
};
