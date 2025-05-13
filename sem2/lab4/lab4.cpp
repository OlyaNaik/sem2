#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "list.h"

using namespace std;

// Структура, представляющая город
struct City
{
    string name;
    string region;
    int population;

    // Оператор сравнения для проверки равенства городов
    bool operator==(const City& other) const
    {
        return name == other.name && region == other.region && population == other.population;
    }
};

// Функция для вывода регионов с суммарным населением
void printRegionsByPopulation(List<City>& cities)
{
    map<string, int> regionPopulation; // Словарь для хранения населения по регионам

    // Подсчет населения для каждого региона
    for (int i = 0; i < cities.count(); i++)
    {
        City city = cities[i];
        regionPopulation[city.region] += city.population;
    }

    // Сортировка регионов по населению в порядке убывания
    vector<pair<string, int>> sortedRegions(regionPopulation.begin(), regionPopulation.end());
    sort(sortedRegions.begin(), sortedRegions.end(), [](const auto& a, const auto& b)
        {
            return a.second > b.second;
        });

    // Вывод регионов и их населения
    for (const auto& region : sortedRegions)
    {
        cout << region.first << ": " << region.second << " жителей" << endl;
    }
}

// Функция для удаления городов по указанному региону
void removeCitiesByRegion(List<City>& cities, const string& region)
{
    for (int i = 0; i < cities.count(); i++)
    {
        if (cities[i].region == region)
        {
            cities.removeAt(i);
            i--;
        }
    }
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "RUS");
    List<City> cities; // Создание списка городов
    int choice;

    do
    {
        cout << "1. Добавить город\n";
        cout << "2. Вывести регионы по населению\n";
        cout << "3. Удалить города по региону\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Добавление города
        {
            City city;
            cout << "Введите название города: ";
            cin.ignore();
            getline(cin, city.name);
            cout << "Введите название региона: ";
            getline(cin, city.region);
            cout << "Введите количество жителей: ";
            cin >> city.population;

            if (cin.fail() || city.population < 0) // Проверка на корректность ввода
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите корректное количество жителей." << endl;
                break;
            }

            cities.add(city);
            break;
        }
        case 2: // Вывод регионов по населению
            printRegionsByPopulation(cities);
            break;
        case 3: // Удаление городов по региону
        {
            string region;
            cout << "Введите название региона для удаления: ";
            cin.ignore();
            getline(cin, region);
            removeCitiesByRegion(cities, region);
            break;
        }
        case 0: // Выход из программы
            break;
        default: // Обработка неверного выбора
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}