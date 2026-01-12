#include <iostream>
#include <set>

class NumberArray {
private:
    std::multiset<double> numbers;

public:
    //Метод для добавления числа в массив
    void addNumber(double num) {
        numbers.insert(num);
    }

    //Метод для вычисления суммы между минимальным и максимальным элементами
    double sumBetweenMinMax() const {
        if (numbers.empty()) {
            std::cout << "Массив пуст." << std::endl;
            return 0.0;
        }

        double minElement = *numbers.begin();
        double maxElement = *numbers.rbegin();
        double sum = 0.0;
        bool between = false;

        for (const auto& num : numbers) {
            if (num == minElement) {
                between = true; //Подсчет после первого минимума
            }
            else if (num == maxElement) {
                break; 
            }
            else if (between) {
                sum += num;
            }
        }

        return sum;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    NumberArray arr;
    double input;

    std::cout << "Введите действительные числа (для завершения введите что-то отличное от числа): " << std::endl;
    while (std::cin >> input) {
        arr.addNumber(input);
    }

    double result = arr.sumBetweenMinMax();
    if (result != 0.0) {
        std::cout << "Сумма элементов между минимальным и максимальным: " << result << std::endl;
    }

    return 0;
}
