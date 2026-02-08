#pragma once

#include "calculator.hpp"
#include "checker.hpp"
#include "parser.hpp"
#include "printer.hpp"

class Runner {
public:
    int Run(int argc, char* argv[]);

private:
    Calculator _calculator;
    Checker _checker;
    Parser _parser;
};
