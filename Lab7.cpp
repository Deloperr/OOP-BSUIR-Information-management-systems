#include <iostream>
#include <cstring>
#include <stdexcept>

class MathException {
protected:
    char op_name[20]; // имя операции
    long val1;        // значение левого операнда операции
    long val2;        // значение правого операнда операции
public:
    MathException(const char* name_op, long v1, long v2) {
        strncpy_s(op_name, name_op, sizeof(op_name) - 1);
        op_name[sizeof(op_name) - 1] = '\0';
        val1 = v1;
        val2 = v2;
    }
    virtual const char* Message() const = 0;
};

// Переполнение сверху
class OverflowException : public MathException {
public:
    OverflowException(long v1, long v2) : MathException("Overflow", v1, v2) {}
    const char* Message() const override {
        static char msg[100];
        snprintf(msg, sizeof(msg), "Ошибка: Переполнение при операции %s с операндами %ld и %ld", op_name, val1, val2);
        return msg;
    }
};

// Переполнение снизу
class UnderflowException : public MathException {
public:
    UnderflowException(long v1, long v2) : MathException("Underflow", v1, v2) {}
    const char* Message() const override {
        static char msg[100];
        snprintf(msg, sizeof(msg), "Ошибка: Переполнение снизу при операции %s с операндами %ld и %ld", op_name, val1, val2);
        return msg;
    }
};

// Деление на 0
class ZdivideException : public MathException {
public:
    ZdivideException(long v1) : MathException("Division by zero", v1, 0) {}
    const char* Message() const override {
        static char msg[100];
        snprintf(msg, sizeof(msg), "Ошибка: Деление на ноль при операции %s с операндом %ld", op_name, val1);
        return msg;
    }
};

// Операции
class Math {
public:
    long Add(long a, long b) {
        if (a > 0 && b > 0 && a > LONG_MAX - b) throw OverflowException(a, b);
        return a + b;
    }

    long Sub(long a, long b) {
        if (a < 0 && b > 0 && a < LONG_MIN + b) throw UnderflowException(a, b);
        return a - b;
    }

    long Mul(long a, long b) {
        if (a > 0 && b > 0 && a > LONG_MAX / b) throw OverflowException(a, b);
        return a * b;
    }

    long Div(long a, long b) {
        if (b == 0) throw ZdivideException(a);
        return a / b;
    }

    long Mod(long a, long b) {
        if (b == 0) throw ZdivideException(a);
        return a % b;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    Math math;
    long a = 9223372036854775807; // LONG_MAX
    long b = 1;

    try {
        std::cout << "Сложение: " << math.Add(a, b) << std::endl;
    }
    catch (const MathException& e) {
        std::cout << e.Message() << std::endl;
    }

    try {
        std::cout << "Вычитание: " << math.Sub(-10, 20) << std::endl;
    }
    catch (const MathException& e) {
        std::cout << e.Message() << std::endl;
    }

    try {
        std::cout << "Умножение: " << math.Mul(a, 2) << std::endl;
    }
    catch (const MathException& e) {
        std::cout << e.Message() << std::endl;
    }

    try {
        std::cout << "Деление: " << math.Div(10, 0) << std::endl;
    }
    catch (const MathException& e) {
        std::cout << e.Message() << std::endl;
    }

    try {
        std::cout << "Остаток: " << math.Mod(10, 0) << std::endl;
    }
    catch (const MathException& e) {
        std::cout << e.Message() << std::endl;
    }

    return 0;
}
