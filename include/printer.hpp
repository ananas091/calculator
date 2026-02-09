#pragma once

#include <string>

#include "types.hpp"

class Printer {
public:
    static void PrintUsage(const std::string& program_name);
    static void PrintResult(const CalculationData& data);
    static void PrintError(const std::string& message);
};
