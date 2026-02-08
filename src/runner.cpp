#include "runner.hpp"

#include <iostream>

#include "logger.hpp"
#include "types.hpp"

int Runner::Run(int argc, char* argv[]) {
    auto& log = Logger::Instance().Get();
    log->info("старт работы калькулятора");
    try {
        CalculationData data;

        _parser.ParseArguments(argc, argv, data);
        _checker.CheckData(data);
        _calculator.Calculate(data);
        Printer::PrintResult(data);

        log->info("вычисление завершено успешно, результат: {}", data.result);

    } catch (const HelpRequestedException&) {
        log->info("запрошена справка");
        Printer::PrintUsage(argv[0]);
        return 0;

    } catch (const std::exception& e) {
        log->error("ошибка: {}", e.what());
        Printer::PrintError(e.what());
        return 1;
    }

    return 0;
}