#include <iostream>
#include <vector>
#include <limits> // Для очистки ввода
#include "admission.h"
#include "admission.cpp"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "ru");

    std::vector<abiturient> abits;
    int n, places;

    while (true) {
        std::cout << "Введите количество абитуриентов: ";
        if (std::cin >> n && n > 0) break;
        std::cout << "Ошибка! Введите положительное число.\n";
        clearInputBuffer();
    }

    while (true) {
        std::cout << "Введите количество мест: ";
        if (std::cin >> places && places >= 0) break;
        std::cout << "Ошибка! Введите неотрицательное число.\n";
        clearInputBuffer();
    }

    for (int i = 0; i < n; ++i) {
        abiturient abit;
        std::cout << "\nАбитуриент #" << i + 1 << std::endl;

        while (true) {
            std::cout << "Средний балл аттестата (0-10): ";
            if (std::cin >> abit.attestat && abit.attestat >= 0 && abit.attestat <= 10) break;
            std::cout << "Ошибка! Введите число от 0 до 10.\n";
            clearInputBuffer();
        }

        auto inputSubject = [](const std::string& prompt) {
            int value;
            while (true) {
                std::cout << prompt;
                if (std::cin >> value && value >= 0 && value <= 100) break;
                std::cout << "Ошибка! Введите число от 0 до 100.\n";
                clearInputBuffer();
            }
            return value;
            };

        abit.subj1 = inputSubject("Первый профильный предмет (0-100): ");
        abit.subj2 = inputSubject("Второй профильный предмет (0-100): ");
        abit.subjLang = inputSubject("Язык (0-100): ");

        abits.push_back(abit);
    }

    int passingScore = admission(abits, places);
    std::cout << "\nРезультаты зачисления:\nПроходной балл: " << passingScore << std::endl;

    for (size_t i = 0; i < abits.size(); ++i) {
        std::cout << "Абитуриент #" << i + 1 << ": Балл = "
            << (abits[i].attestat * 10 + abits[i].subj1 + abits[i].subj2 + abits[i].subjLang)
            << ", Статус = " << (abits[i].student ? "Зачислен" : "Не зачислен") << std::endl;
    }

    return 0;
}