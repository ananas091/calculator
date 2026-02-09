#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "runner.hpp"

class CalculatorTest : public ::testing::Test {
protected:
    std::stringstream out;
    std::stringstream err;
    std::streambuf* orig_out{};
    std::streambuf* orig_err{};

    void SetUp() override {
        orig_out = std::cout.rdbuf(out.rdbuf());
        orig_err = std::cerr.rdbuf(err.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(orig_out);
        std::cerr.rdbuf(orig_err);
    }

    int Run(std::vector<std::string> args) {
        std::vector<char*> argv;
        for (auto& a : args) {
            argv.push_back(a.data());
        }
        Runner runner;
        return runner.Run(static_cast<int>(argv.size()), argv.data());
    }
};

// Успешные вычисления

TEST_F(CalculatorTest, Add) {
    EXPECT_EQ(Run({"calc", R"({"operand1":2.54,"operation":"+","operand2":-3})"}), 0);
    EXPECT_EQ(out.str(), "-0.46\n");
}

TEST_F(CalculatorTest, Sub) {
    EXPECT_EQ(Run({"calc", R"({"operand1":10,"operation":"-","operand2":10})"}), 0);
    EXPECT_EQ(out.str(), "0\n");
}

TEST_F(CalculatorTest, Mul) {
    EXPECT_EQ(Run({"calc", R"({"operand1":3.33,"operation":"*","operand2":3})"}), 0);
    EXPECT_EQ(out.str(), "9.99\n");
}

TEST_F(CalculatorTest, Div) {
    EXPECT_EQ(Run({"calc", R"({"operand1":12,"operation":"/","operand2":-5})"}), 0);
    EXPECT_EQ(out.str(), "-2.4\n");
}

TEST_F(CalculatorTest, Pow) {
    EXPECT_EQ(Run({"calc", R"({"operand1":2,"operation":"^","operand2":10})"}), 0);
    EXPECT_EQ(out.str(), "1024\n");
}

TEST_F(CalculatorTest, Fact) {
    EXPECT_EQ(Run({"calc", R"({"operand1":5,"operation":"!"})"}), 0);
    EXPECT_EQ(out.str(), "120\n");
}

TEST_F(CalculatorTest, FactZero) {
    EXPECT_EQ(Run({"calc", R"({"operand1":0,"operation":"!"})"}), 0);
    EXPECT_EQ(out.str(), "1\n");
}

// Ошибки

TEST_F(CalculatorTest, DivByZero) {
    EXPECT_EQ(Run({"calc", R"({"operand1":10,"operation":"/","operand2":0})"}), 1);
    EXPECT_EQ(err.str(), "Ошибка: Division by zero\n");
}

TEST_F(CalculatorTest, NegativeFactorial) {
    EXPECT_EQ(Run({"calc", R"({"operand1":-5,"operation":"!"})"}), 1);
    EXPECT_EQ(err.str(), "Ошибка: факториал определён только для неотрицательных чисел\n");
}

TEST_F(CalculatorTest, FloatFactorial) {
    EXPECT_EQ(Run({"calc", R"({"operand1":3.5,"operation":"!"})"}), 1);
    EXPECT_EQ(err.str(), "Ошибка: факториал определён только для целых чисел\n");
}

TEST_F(CalculatorTest, InvalidJson) {
    EXPECT_EQ(Run({"calc", "not json"}), 1);
    EXPECT_NE(err.str().find("Ошибка: ошибка парсинга JSON:"), std::string::npos);
}

TEST_F(CalculatorTest, MissingOperation) {
    EXPECT_EQ(Run({"calc", R"({"operand1":1,"operand2":2})"}), 1);
    EXPECT_EQ(err.str(), "Ошибка: отсутствует поле 'operation'\n");
}

TEST_F(CalculatorTest, UnknownOperation) {
    EXPECT_EQ(Run({"calc", R"({"operand1":1,"operation":"%","operand2":2})"}), 1);
    EXPECT_NE(err.str().find("Ошибка: неизвестная операция"), std::string::npos);
}

TEST_F(CalculatorTest, NoArgs) {
    EXPECT_EQ(Run({"calc"}), 1);
    EXPECT_NE(err.str().find("Ошибка: недостаточно аргументов."), std::string::npos);
}

// Help

TEST_F(CalculatorTest, Help) {
    EXPECT_EQ(Run({"calc", "--help"}), 0);
    EXPECT_NE(out.str().find("Использование:"), std::string::npos);
}
