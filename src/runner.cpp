#include "runner.hpp"

#include <iostream>

#include "types.hpp"

int Runner::Run(int argc, char* argv[]) {
    try {
        CalculationData data;

        _parser.ParseArguments(argc, argv, data);
        _checker.CheckData(data);
        _calculator.Calculate(data);
        Printer::PrintResult(data);

    } catch (const HelpRequestedException&) {
        Printer::PrintUsage(argv[0]);
        return 0;

    } catch (const std::exception& e) {
        Printer::PrintError(e.what());
        return 1;
    }

    return 0;
}