#include <errno.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mathlib.hpp"
#include "runner.hpp"

int main(int argc, char* argv[]) {
    Runner runner;
    return runner.run(argc, argv);
}
