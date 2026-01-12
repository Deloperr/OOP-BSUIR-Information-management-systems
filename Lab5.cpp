#include <iostream>
#include <cstring>
#include <cstdio> 

class Person {
protected:
    char fio[100];              // ФИО
    char date_of_birth[12];     // Дата рождения
    char pol[5];                // Пол
    Person* next;               // Указатель на следующего в списке

public:
    Person() : next(nullptr) {}

    void SetPersonInfo(const char* name, const char* birth_date, const char* gender) {
        strncpy_s(fio, name, sizeof(fio) - 1);
        strncpy_s(date_of_birth, birth_date, sizeof(date_of_birth) - 1);
        strncpy_s(pol, gender, sizeof(pol) - 1);
    }

    virtual void PersonInfo() {
        std::cout << "ФИО: " << fio << ", Дата рождения: " << date_of_birth << ", Пол: " << pol << std::endl;
    }

    // Метод для получения указателя на следующий элемент
    Person* GetNext() {
        return next;
    }

    // Метод для установки следующего элемента
    void SetNext(Person* nextPerson) {
        next = nextPerson;
    }
};

class Employee : public Person {
protected:
    char position[50];           // Должность

public:
    void SetPosition(const char* pos) {
        strncpy_s(position, pos, sizeof(position) - 1);
    }

    virtual void PersonInfo() override {
        Person::PersonInfo();
        std::cout << "Должность: " << position << std::endl;
    }
};

class Manager : public Employee {
private:
    char department[50];         // Наименование отдела
    Person* employees;           // Указатель на список сотрудников

public:
    Manager(const char* dept) {
        strncpy_s(department, dept, sizeof(department) - 1);
        employees = nullptr;
    }

    void SetDepartment(const char* dept) {
        strncpy_s(department, dept, sizeof(department) - 1);
    }

    void AddEmployee(Person* emp) {
        emp->SetNext(employees); // Метод для установки следующего элемента
        employees = emp;
    }

    void PersonInfo() override {
        Employee::PersonInfo();
        std::cout << "Отдел: " << department << std::endl;
        std::cout << "Сотрудники:" << std::endl;
        Person* current = employees;
        while (current) {
            current->PersonInfo();
            current = current->GetNext(); // Метод для получения следующего элемента
        }
    }
};

class Chief : public Employee {
private:
    char firm[50];               // Наименование фирмы
    Manager* managers;           // Указатель на список менеджеров

public:
    Chief(const char* firm_name) {
        strncpy_s(firm, firm_name, sizeof(firm) - 1);
        managers = nullptr;
    }

    void AddManager(Manager* mgr) {
        mgr->SetNext(managers); // Метод для установки следующего элемента
        managers = mgr;
    }

    void PersonInfo() override {
        Employee::PersonInfo();
        std::cout << "Фирма: " << firm << std::endl;
        std::cout << "Менеджеры:" << std::endl;
        Person* current = managers;
        while (current) {
            current->PersonInfo();
            current = current->GetNext(); // Метод для получения следующего элемента
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    Chief* ch = new Chief("Рога и Копыта");
    ch->SetPersonInfo("Остап Бендер", "12.12.1212", "м");

    Manager* m1 = new Manager("Рога");
    m1->SetPersonInfo("Шура", "01.01.0101", "м");
    m1->SetPosition("Менеджер по продажам");

    Manager* m2 = new Manager("Копыта");
    m2->SetPersonInfo("Паниковский", "10.10.1010", "м");
    m2->SetPosition("Менеджер по закупкам");

    for (int i = 0; i < 3; ++i) {
        Person* emp = new Person();
        char name[100];
        snprintf(name, sizeof(name), "Сотрудник %d", i + 1);
        emp->SetPersonInfo(name, "01.01.2000", "м");
        m1->AddEmployee(emp);
    }

    for (int i = 0; i < 3; ++i) {
        Person* emp = new Person();
        char name[100];
        snprintf(name, sizeof(name), "Сотрудник %d", i + 1);
        emp->SetPersonInfo(name, "01.01.2000", "ж");
        m2->AddEmployee(emp);
    }

    ch->AddManager(m1);
    ch->AddManager(m2);

    ch->PersonInfo();

    delete ch;

    return 0;
}
