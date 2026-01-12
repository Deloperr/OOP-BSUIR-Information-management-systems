#include <iostream>

class Date {
public:
    // Конструктор по умолчанию
    Date() : years(0), months(0), days(0) {}

    // Конструктор с параметрами
    Date(unsigned year, unsigned month, unsigned day) : years(year), months(month), days(day) {
        if (!isValidDate(years, months, days)) {
            years = 0; months = 0; days = 0; // Устанавливаем некорректную дату в 0
        }
    }

    // Конструктор копирования
    Date(const Date& other) : years(other.years), months(other.months), days(other.days) {}

    ~Date();
    // Функция для чтения даты из потока ввода
    void inputDate() {
        std::cout << "Введите год: ";
        std::cin >> years;
        std::cout << "Введите месяц: ";
        std::cin >> months;
        std::cout << "Введите день: ";
        std::cin >> days;

        while (!isValidDate(years, months, days)) {
            std::cout << "Некорректная дата! Пожалуйста, введите дату снова." << std::endl;
            inputDate();
        }
    }

    // Функция для вывода даты
    void outputDate() const {
        std::cout << "Дата: " << days << "." << months << "." << years << std::endl;
    }

    // Функция для добавления времени к дате
    void addDate(unsigned addY = 0, unsigned addM = 0, unsigned addD = 0) {
        days += addD;
        while (!isValidDate(years, months, days)) {
            days -= 30;
            months++;
            if (months > 12) {
                months = 1;
                years++;
            }
        }

        months += addM;
        while (months > 12) {
            months -= 12;
            years++;
        }

        years += addY;
    }

    // Дружественная функция для вычисления разницы в днях между двумя датами
    friend unsigned daysBetween(const Date& date1, const Date& date2);
private:
    unsigned years;   // год
    unsigned months;  // месяц
    unsigned days;    // день

    // Проверка корректности даты
    bool isValidDate(unsigned years, unsigned months, unsigned days) const {
        if (months < 1 || months > 12) return false;
        if (days < 1) return false;

        unsigned daysInMonth;
        if (months == 2) {
            daysInMonth = (years % 4 == 0 && (years % 100 != 0 || years % 400 == 0)) ? 29 : 28;
        }
        else if (months == 4 || months == 6 || months == 9 || months == 11) {
            daysInMonth = 30;
        }
        else {
            daysInMonth = 31;
        }

        return days <= daysInMonth;
    }

};

// Функция для вычисления разницы в днях
unsigned daysBetween(const Date& date1, const Date& date2) {
    auto totalDays = [](const Date& date) {
        unsigned days = date.days;
        for (unsigned years = 1; years < date.years; ++years) {
            days += (years % 4 == 0 && (years % 100 != 0 || years % 400 == 0)) ? 366 : 365;
        }
        for (unsigned months = 1; months < date.months; ++months) {
            days += (months == 2) ? (date.years % 4 == 0 && (date.years % 100 != 0 || date.years % 400 == 0) ? 29 : 28) :
                (months == 4 || months == 6 || months == 9 || months == 11) ? 30 : 31;
        }
        return days;
        };

    return totalDays(date2) > totalDays(date1) ? totalDays(date2) - totalDays(date1) : totalDays(date1) - totalDays(date2);
}

int main() {
    setlocale(LC_ALL, "RU");
    Date date1, date2;

    std::cout << "Введите первую дату:" << std::endl;
    date1.inputDate();

    std::cout << "Введите вторую дату:" << std::endl;
    date2.inputDate();

    date1.outputDate();
    date2.outputDate();

    unsigned years, months, days;

    std::cout << "Сколько лет добавить к 1 дате:" << std::endl;
    std::cin >> years;
    std::cout << "Сколько месяцев добавить к 1 дате:" << std::endl;
    std::cin >> months;
    std::cout << "Сколько дней добавить к 1 дате:" << std::endl;
    std::cin >> days;
    date1.addDate(years, months, days);
    std::cout << "После добавления даты:" << std::endl;
    date1.outputDate();

    std::cout << "Сколько лет добавить ко 2 дате:" << std::endl;
    std::cin >> years;
    std::cout << "Сколько месяцев добавить ко 2 дате:" << std::endl;
    std::cin >> months;
    std::cout << "Сколько дней добавить ко 2 дате:" << std::endl;
    std::cin >> days;
    date2.addDate(years, months, days);
    std::cout << "После добавления даты:" << std::endl;
    date2.outputDate();

    unsigned daysDifference = daysBetween(date1, date2);
    std::cout << "Количество дней между датами: " << daysDifference << " дней" << std::endl;

    return 0;
}
