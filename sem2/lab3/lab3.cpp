#include <iostream>
#include "cyclelist.h"

using namespace std; // Добавлено использование пространства имен std

// Функция для вставки единицы перед каждым отрицательным числом в списке
void insertBeforeNegatives(CycleList<int>& list) {
    for (int i = 0; i < list.count(); i++) {
        if (list[i] < 0) {
            list.insert(i, 1);
            i++; // Пропускаем только что вставленный элемент
        }
    }
}

// Функция для удаления всех отрицательных чисел из списка
void removeNegatives(CycleList<int>& list) {
    for (int i = 0; i < list.count(); ) {
        if (list[i] < 0) {
            list.removeAt(i);
        }
        else {
            i++;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    CycleList<int> queue; // Создаем экземпляр циклического списка
    int choice, value, index;

    do {
        // Меню для взаимодействия с пользователем
        cout << "Меню:\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Вставить элемент по позиции\n";
        cout << "3. Удалить элемент по позиции\n";
        cout << "4. Получить элемент по индексу\n";
        cout << "5. Подсчитать количество элементов\n";
        cout << "6. Подсчитать количество вхождений значения\n";
        cout << "7. Очистить список\n";
        cout << "8. Вставить 1 перед каждым отрицательным числом\n";
        cout << "9. Удалить все отрицательные числа\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт меню: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите значение: ";
            cin >> value;
            queue.add(value);
            break;
        case 2:
            cout << "Введите индекс и значение: ";
            cin >> index >> value;
            try {
                queue.insert(index, value);
            }
            catch (const out_of_range& e) {
                cout << e.what() << endl;
            }
            break;
        case 3:
            cout << "Введите индекс для удаления: ";
            cin >> index;
            try {
                queue.removeAt(index);
            }
            catch (const out_of_range& e) {
                cout << e.what() << endl;
            }
            break;
        case 4:
            cout << "Введите индекс для доступа: ";
            cin >> index;
            try {
                cout << "Элемент: " << queue[index] << endl;
            }
            catch (const out_of_range& e) {
                cout << e.what() << endl;
            }
            break;
        case 5:
            cout << "Количество элементов: " << queue.count() << endl;
            break;
        case 6:
            cout << "Введите значение для подсчета: ";
            cin >> value;
            cout << "Количество вхождений: " << queue.count(value) << endl;
            break;
        case 7:
            queue.clear();
            cout << "Список очищен.\n";
            break;
        case 8:
            insertBeforeNegatives(queue);
            cout << "Вставлено 1 перед отрицательными числами.\n";
            break;
        case 9:
            removeNegatives(queue);
            cout << "Удалены отрицательные числа.\n";
            break;
        case 0:
            cout << "Выход...\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}