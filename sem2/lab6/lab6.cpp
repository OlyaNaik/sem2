#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include "tree.h"

using namespace std;

// Функция для вывода меню
void printMenu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Добавить элемент в дерево\n";
    cout << "2. Удалить элемент из дерева\n";
    cout << "3. Проверить, содержится ли элемент\n";
    cout << "4. Очистить дерево\n";
    cout << "5. Вывести дерево (в виде списка)\n";
    cout << "6. Вращение дерева влево относительно узла\n";
    cout << "7. Вращение дерева вправо относительно узла\n";
    cout << "8. Подсчитать количество элементов\n";
    cout << "9. Выйти\n";
    cout << "Выберите команду: ";
}

// Функция для выбора способа обхода дерева
void printOrderOptions() {
    cout << "\nВыберите способ обхода дерева:\n";
    cout << "1. Infix (сред. порядок)\n";
    cout << "2. Prefix (прямой порядок)\n";
    cout << "3. Postfix (обратный порядок)\n";
    cout << "Ваш выбор: ";
}

// Главная функция программы
int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "RUS");
    Tree<int> tree(false); // Создание дерева поиска без автоматической балансировки

    int choice;
    int elem;
    int orderChoice;
    bool running = true;

    while (running) {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1: // Добавление элемента
            cout << "Введите значение, которое хотите добавить: ";
            cin >> elem;
            tree.add(elem);
            cout << "Элемент добавлен.\n";
            break;

        case 2: // Удаление элемента
            cout << "Введите значение, которое хотите удалить: ";
            cin >> elem;
            tree.remove(elem);
            cout << "Удаление выполнено (если элемент существовал).\n";
            break;

        case 3: // Проверка на содержание
            cout << "Введите значение для проверки: ";
            cin >> elem;
            if (tree.contains(elem)) {
                cout << "Элемент содержится в дереве.\n";
            }
            else {
                cout << "Элемент НЕ содержится в дереве.\n";
            }
            break;

        case 4: // Очистить дерево
            tree.clear();
            cout << "Дерево очищено.\n";
            break;

        case 5: // Вывод дерева
            printOrderOptions();
            cin >> orderChoice;

            {
                Tree<int>::Order order;
                switch (orderChoice) {
                case 1: order = Tree<int>::Infix; break;
                case 2: order = Tree<int>::Prefix; break;
                case 3: order = Tree<int>::Postfix; break;
                default:
                    cout << "Неверный выбор! Используется Infix.\n";
                    order = Tree<int>::Infix;
                }

                vector<int> treeList = tree.ToList(order);
                cout << "Дерево в виде списка: [";
                for (size_t i = 0; i < treeList.size(); ++i) {
                    cout << treeList[i];
                    if (i < treeList.size() - 1) cout << ", ";
                }
                cout << "]\n";
            }
            break;

        case 6: // Поворот влево
            cout << "Введите значение узла для вращения влево: ";
            cin >> elem;
            tree.ToLeft(elem);
            cout << "Поворот выполнен (если узел существует).\n";
            break;

        case 7: // Поворот вправо
            cout << "Введите значение узла для вращения вправо: ";
            cin >> elem;
            tree.ToRight(elem);
            cout << "Поворот выполнен (если узел существует).\n";
            break;

        case 8: // Подсчитать количество элементов
            cout << "Количество элементов в дереве: " << tree.count() << "\n";
            break;

        case 9: // Выход
            running = false;
            cout << "Выход из программы.\n";
            break;

        default: // Неверная команда
            cout << "Неверная команда. Попробуйте снова.\n";
        }
    }

    return 0;
}