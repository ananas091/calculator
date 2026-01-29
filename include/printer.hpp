#pragma once

#include "types.hpp"

class Printer {
public:
    void print_usage(const char* program_name);
    void print_result(const CalculationData* data);
private:
};