#include "runner.hpp"

#include "types.hpp"

int Runner::run(int argc, char* argv[]) {
    CalculationData data;

    if (int parser_code = _parser.parse_arguments(argc, argv, &data); parser_code < 0) {
        if (parser_code == -2) {
            _printer.print_usage(argv[0]);
        }
        return 1;
    }

    if (_checker.check_data(&data) < 0) {
        return 1;
    }

    _calculator.calculate(&data);
    _printer.print_result(&data);

    return data.error ? 1 : 0;
}