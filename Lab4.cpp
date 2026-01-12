#include <iostream>

class Date {
public:
    Date() : years(0), months(0), days(0) {}
    Date(int y, int m, int d) : years(y), months(m), days(d) {
        if (!isValidDate(years, months, days)) years = months = days = 0;
    }
    Date(const Date& other) = default;
    Date& operator=(const Date& other) = default;

    Date& operator+=(const Date& other) {
        days += other.days; months += other.months; years += other.years; normalize();
        return *this;
    }

    Date& operator-=(const Date& other) {
        days -= other.days; months -= other.months; years -= other.years;
        normalize(); // Нормализация после вычитания
        return *this;
    }

    Date& operator+=(int d) { days += d; normalize(); return *this; }
    Date& operator-=(int d) {
        days -= d;
        while (days < 1) {
            --months;
            if (months < 1) {
                months = 12; --years;
            }
            days += (months == 2) ? (isLeapYear(years) ? 29 : 28) :
                (months == 4 || months == 6 || months == 9 || months == 11) ? 30 : 31;
        }
        normalize(); // Нормализация после вычитания
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
private:
    int years, months, days;

    bool isValidDate(int y, int m, int d) const {
        if (m < 1 || m > 12 || d < 1) return false;
        int daysInMonth = (m == 2) ? (isLeapYear(y) ? 29 : 28) :
            (m == 4 || m == 6 || m == 9 || m == 11) ? 30 : 31;
        return d <= daysInMonth;
    }

    void normalize() {
        while (days < 1) {
            if (--months < 1) { months = 12; --years; }
            days += (months == 2) ? (isLeapYear(years) ? 29 : 28) : (months == 4 || months == 6 || months == 9 || months == 11) ? 30 : 31;
        }
        while (days > 31) {
            days -= 31; ++months;
        }
        while (months > 12) {
            months -= 12; ++years;
        }
        while (months < 1) {
            months += 12; --years;
        }
    }

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

};

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.days << "." << date.months << "." << date.years;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    do {
        std::cout << "Введите дату (год месяц день): ";
        is >> date.years >> date.months >> date.days;
        if (!date.isValidDate(date.years, date.months, date.days))
            std::cout << "Некорректная дата! Попробуйте снова." << std::endl;
    } while (!date.isValidDate(date.years, date.months, date.days));
    return is;
}

int main() {
    setlocale(LC_ALL, "RU");
    Date date1, date2, date3;

    std::cout << "Введите первую дату:" << std::endl;
    std::cin >> date1;

    std::cout << "Введите вторую дату:" << std::endl;
    std::cin >> date2;

    std::cout << "Первая дата: " << date1 << std::endl;
    std::cout << "Вторая дата: " << date2 << std::endl;

    date1 += date2; // Добавление второй даты к первой
    std::cout << "После добавления: " << date1 << std::endl;

    int daysToAdd;
    std::cout << "Сколько дней добавить к первой дате: ";
    std::cin >> daysToAdd;
    date1 += daysToAdd;
    std::cout << "После добавления дней: " << date1 << std::endl;

    date1 -= date2; // Вычитание второй даты из первой
    std::cout << "После вычитания: " << date1 << std::endl;

    int daysToSubtract;
    std::cout << "Сколько дней вычесть из первой даты: ";
    std::cin >> daysToSubtract;
    date1 -= daysToSubtract;
    std::cout << "После вычитания дней: " << date1 << std::endl;

    // Копирование первой даты во вторую
    date3 = date1;
    std::cout << "Третья дата (копия первой): " << date3 << std::endl;

    return 0;
}
