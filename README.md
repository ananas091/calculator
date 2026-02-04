# Calculator

Консольный калькулятор на C++ с использованием библиотеки MathLib.

## Что это?

Калькулятор с поддержкой базовых математических операций и обработкой переполнения:

* Сложение, вычитание, умножение, деление
* Возведение в степень
* Факториал

## Зависимости

Проект использует:
- [MathLib](https://github.com/ananas091/mathlib) для безопасных математических вычислений с обнаружением переполнения
- [nlohmann/json](https://github.com/nlohmann/json) для парсинга JSON

## Формат входных данных

Входные данные подаются в формате JSON.

### Бинарные операции (+, -, *, /, ^)

```json
{
    "operand1": 10,
    "operation": "+",
    "operand2": 5
}
```

### Унарная операция (факториал)

```json
{
    "operand1": 5,
    "operation": "!"
}
```

## Сборка

### Локально

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Debug-сборка с санитайзерами

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

### Установка

```bash
cmake --build . --target install
```

## Использование

### JSON строка напрямую

```bash
./calculator '{"operand1": 10, "operation": "+", "operand2": 5}'
# Вывод: 15

./calculator '{"operand1": 5, "operation": "!"}'
# Вывод: 120
```

### JSON из файла

```bash
echo '{"operand1": 100, "operation": "/", "operand2": 4}' > input.json
./calculator -f input.json
# Вывод: 25
```

### Справка

```bash
./calculator -h
./calculator --help
```
