#include <iostream>
#include <string>
#define NOMINMAX
#include <Windows.h>
#include "dictionary.h"

using namespace std;

// Функция для отображения меню
void displayMenu()
{
    cout << "Меню:\n";
    cout << "1. Добавить пару ключ-значение\n";
    cout << "2. Удалить ключ\n";
    cout << "3. Получить значение по ключу\n";
    cout << "4. Показать все ключи\n";
    cout << "5. Показать все значения\n";
    cout << "6. Очистить словарь\n";
    cout << "7. Выход\n";
    cout << "Выберите опцию: ";
}

int main()
{
    // Установка кодировки для корректного отображения русских символов
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "RUS");

    // Создание экземпляра словаря, где ключи - строки, а значения - целые числа
    Dictionary<string, int> dict;
    int choice;
    string key;
    int value;

    while (true)
    {
        displayMenu();
        cin >> choice;

        // Проверка на корректность ввода
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: Пожалуйста, введите числовое значение." << endl;
            continue;
        }

        switch (choice)
        {
        case 1: // Добавить пару ключ-значение
            cout << "Введите ключ: ";
            cin >> key;
            cout << "Введите значение: ";
            cin >> value;
            dict.add(key, value);
            cout << "Добавлено: " << key << " -> " << value << endl;
            break;

        case 2: // Удалить ключ
            cout << "Введите ключ для удаления: ";
            cin >> key;
            dict.remove(key);
            cout << "Удалено: " << key << endl;
            break;

        case 3: // Получить значение по ключу
            cout << "Введите ключ для получения значения: ";
            cin >> key;
            if (dict.TryGetValue(key, value))
            {
                cout << "Значение для '" << key << "': " << value << endl;
            }
            else
            {
                cout << "Ключ '" << key << "' не найден." << endl;
            }
            break;

        case 4: // Показать все ключи
        {
            auto keys = dict.GetKeys();
            cout << "Ключи: ";
            for (const auto& k : keys)
            {
                cout << k << " ";
            }
            cout << endl;
        }
        break;

        case 5: // Показать все значения
        {
            auto values = dict.GetValues();
            cout << "Значения: ";
            for (const auto& val : values)
            {
                cout << val << " ";
            }
            cout << endl;
        }
        break;

        case 6: // Очистить словарь
            dict.clear();
            cout << "Словарь очищен." << endl;
            break;

        case 7: // Выход
            cout << "Выход из программы." << endl;
            return 0;

        default: // Обработка неверного выбора
            cout << "Неверная опция. Пожалуйста, попробуйте снова." << endl;
            break;
        }
    }
}