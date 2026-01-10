#include "mathlib.h"

#include <stdexcept>

namespace mathlib {

double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }

double div(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("division by zero");
    }
    return a / b;
}

double pow(double base, long long exp) {
    if (exp == 0) return 1.0;

    const bool negative = (exp < 0);
    unsigned long long e = negative ? static_cast<unsigned long long>(-exp) : static_cast<unsigned long long>(exp);

    double result = 1.0;
    for (unsigned long long i = 0; i < e; ++i) {
        result *= base;
    }

    if (negative) {
        if (result == 0.0) {
            throw std::runtime_error("0 cannot be raised to a negative power");
        }
        result = 1.0 / result;
    }

    return result;
}

long long factorial(long long n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

}  // namespace mathlib
