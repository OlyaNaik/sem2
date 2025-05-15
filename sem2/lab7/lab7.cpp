#include <iostream>
#include <string>
#include <vector>
#define NOMINMAX
#include <Windows.h>
#include "set.h"

using namespace std;

// Функция для отображения меню
void printMenu() {
    cout << "\n==== Меню Хеш-Множества ====\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Удалить элемент\n";
    cout << "3. Проверить наличие элемента\n";
    cout << "4. Узнать количество элементов\n";
    cout << "5. Очистить множество\n";
    cout << "6. Преобразовать множество в список и вывести\n";
    cout << "0. Выйти\n";
    cout << "Введите ваш выбор: ";
}

int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "RUS");

    Set<string> mySet;
    int choice;
    string value;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1: // Добавление элемента
            cout << "Введите значение для добавления: ";
            cin >> value;
            mySet.add(value);
            cout << "Значение добавлено.\n";
            break;

        case 2: // Удаление элемента
            cout << "Введите значение для удаления: ";
            cin >> value;
            mySet.remove(value);
            cout << "Значение удалено (если оно существовало).\n";
            break;

        case 3: // Проверка наличия элемента
            cout << "Введите значение для проверки: ";
            cin >> value;
            if (mySet.contains(value)) {
                cout << "Значение содержится в множестве.\n";
            }
            else {
                cout << "Значение отсутствует в множестве.\n";
            }
            break;

        case 4: // Узнать количество элементов
            cout << "Множество содержит " << mySet.count() << " элементов.\n";
            break;

        case 5: // Очистка множества
            mySet.clear();
            cout << "Множество очищено.\n";
            break;

        case 6: { // Преобразование множества в список и вывод
            vector<string> list = mySet.toList();
            cout << "Множество как список: ";
            for (const auto& val : list) {
                cout << val << " ";
            }
            cout << "\n";
            break;
        }

        case 0: // Выход из программы
            cout << "Выход...\n";
            break;

        default: // Обработка неверного выбора
            cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    } while (choice != 0); // Цикл продолжается, пока пользователь не выберет выход

    return 0; // Завершение программы
}