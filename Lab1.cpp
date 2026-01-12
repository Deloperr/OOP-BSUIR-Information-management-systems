#include <iostream>

struct Date {
    unsigned years; //год
    unsigned months; //месяц
    unsigned days; //день
};

//функция для проверки корректности даты
bool isValidDate(unsigned years, unsigned months, unsigned days) {
    if (months < 1 || months > 12) return false;
    if (days < 1) return false;

    //определяем количество дней в месяце
    unsigned daysInMonth;
    if (months == 2) {
        //проверка на високосный год
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

//функция для чтения даты из потока ввода
void inputDate(Date& date) {
    std::cout << "Введите год: ";
    std::cin >> date.years;
    std::cout << "Введите месяц: ";
    std::cin >> date.months;
    std::cout << "Введите день: ";
    std::cin >> date.days;

    while (!isValidDate(date.years, date.months, date.days)) {
        std::cout << "Некорректная дата! Пожалуйста, введите дату снова." << std::endl;
        std::cout << "Введите год: ";
        std::cin >> date.years;
        std::cout << "Введите месяц: ";
        std::cin >> date.months;
        std::cout << "Введите день: ";
        std::cin >> date.days;
    }
}

//функция для вывода даты
void outputDate(const Date& date) {
    std::cout << "Дата: " << date.days << "." << date.months << "." << date.years << std::endl;
}

//функция для добавления времени к дате с параметрами по умолчанию
void addDate(Date& date, unsigned addY = 0, unsigned addM = 0, unsigned addD = 0) {
    date.days += addD;
    while (!isValidDate(date.years, date.months, date.days)) {
        date.days -= 30;
        date.months++;
        if (date.months > 12) {
            date.months = 1;
            date.years++;
        }
    }

    date.months += addM;
    while (date.months > 12) {
        date.months -= 12;
        date.years++;
    }

    date.years += addY;
}

//функция для вычисления разницы в днях между двумя датами
unsigned daysBetween(const Date& date1, const Date& date2) {
    //преобразуем даты в дни
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
    int years, months, days;
    std::cout << "Введите первую дату:" << std::endl;
    inputDate(date1);

    std::cout << "Введите вторую дату:" << std::endl;
    inputDate(date2);

    outputDate(date1);
    outputDate(date2);

    //добавление даты
    std::cout << "Сколько лет добавить к 1 дате:" << std::endl;
    std::cin >> years;
    std::cout << "Сколько месяцев добавить к 1 дате:" << std::endl;
    std::cin >> months;
    std::cout << "Сколько дней добавить к 1 дате:" << std::endl;
    std::cin >> days;
    addDate(date1, years, months, days);
    std::cout << "После добавления даты:" << std::endl;
    outputDate(date1);

    std::cout << "Сколько лет добавить ко 2 дате:" << std::endl;
    std::cin >> years;
    std::cout << "Сколько месяцев добавить ко 2 дате:" << std::endl;
    std::cin >> months;
    std::cout << "Сколько дней добавить ко 2 дате:" << std::endl;
    std::cin >> days;
    addDate(date2, years, months, days);
    std::cout << "После добавления даты:" << std::endl;
    outputDate(date2);

    //вычисление разницы в днях между двумя датамиф
    unsigned daysDifference = daysBetween(date1, date2);
    std::cout << "Количество дней между датами: " << daysDifference << " дней" << std::endl;

    return 0;
}
