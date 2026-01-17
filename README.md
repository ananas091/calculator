# Calculator

Консольный калькулятор на C++ с использованием библиотеки MathLib.

## Что это?

Калькулятор с поддержкой базовых математических операций и обработкой переполнения:

* Сложение, вычитание, умножение, деление
* Возведение в степень
* Факториал

## Зависимости

Проект использует [MathLib](https://github.com/ananas091/mathlib) для безопасных математических вычислений с обнаружением переполнения.

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

### Запуск справки

```bash
./calculator -h или --help
```
