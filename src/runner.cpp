#include "runner.hpp"

#include <format>
#include <iostream>

#include "logger.hpp"
#include "types.hpp"

int Runner::Run(int argc, char* argv[]) {
    auto& log = Logger::Instance();
    log.Info("calculator start");
    try {
        CalculationData data;

        _parser.ParseArguments(argc, argv, data);
        _checker.CheckData(data);
        _calculator.Calculate(data);
        Printer::PrintResult(data);

        log.Info(std::format("calculation completed successfully, result: {}", data.result));

    } catch (const HelpRequestedException&) {
        log.Info("help requested");
        Printer::PrintUsage(argv[0]);
        return 0;

    } catch (const std::exception& e) {
        log.Error(std::format("error: {}", e.what()));
        Printer::PrintError(e.what());
        return 1;
    }

    return 0;
}
