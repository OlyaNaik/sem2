#include <iostream>
#include "queue.h" // Подключение заголовочного файла с определением класса Queue

using namespace std;

// Функция для отображения меню
int displayMenu()
{
    int choice;
    cout << "\nМеню:\n";
    cout << "1. Добавить элемент в очередь\n";
    cout << "2. Извлечь элемент из очереди\n";
    cout << "3. Показать количество элементов\n";
    cout << "4. Очистить очередь\n";
    cout << "5. Вставить 1 перед каждым отрицательным числом\n";
    cout << "6. Удалить все отрицательные числа\n";
    cout << "7. Подсчитать вхождения числа\n";
    cout << "8. Вывести очередь\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
    cin >> choice;
    return choice;
}

// Функция для вставки 1 перед каждым отрицательным числом в очереди
template <typename T>
void insertBeforeNegatives(Queue<T>& q)
{
    Queue<T> tempQueue;
    int originalSize = q.count();

    for (int i = 0; i < originalSize; ++i)
    {
        T value = q.unqueue();
        if (value < 0)
        {
            tempQueue.queue(1); // Вставка 1 перед отрицательным числом
        }
        tempQueue.queue(value);
    }

    // Перенос элемента обратно в оригинальную очередь
    while (tempQueue.count() > 0)
    {
        q.queue(tempQueue.unqueue());
    }
}

// Функция для удаления всех отрицательных элементов из очереди
template <typename T>
void removeNegatives(Queue<T>& q)
{
    Queue<T> tempQueue;
    int originalSize = q.count();

    for (int i = 0; i < originalSize; ++i)
    {
        T value = q.unqueue();
        if (value >= 0)
        {
            tempQueue.queue(value); // Добавление положительных элементов
        }
    }

    // Перенос обратно положительных элементов в оригинальную очередь
    while (tempQueue.count() > 0)
    {
        q.queue(tempQueue.unqueue());
    }
}

// Функция для подсчета количества вхождений заданного значения в очереди
template <typename T>
int countOccurrences(Queue<T>& q, T value)
{
    int count = 0;
    int originalSize = q.count();

    for (int i = 0; i < originalSize; ++i)
    {
        T currentValue = q.unqueue();
        if (currentValue == value)
        {
            count++;
        }
        q.queue(currentValue); // Возвращение элемента обратно в очередь
    }
    return count;
}

// Функция для вывода элементов очереди
template <typename T>
void printQueue(Queue<T>& q)
{
    int originalSize = q.count();
    cout << "Элементы очереди: ";
    for (int i = 0; i < originalSize; ++i)
    {
        T value = q.unqueue();
        cout << value << " ";
        q.queue(value); // Возврат элемента обратно в очередь
    }
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    Queue<int> q; // Создание очереди для хранения целых чисел
    int choice, value; // Переменные для выбора опции и значения

    do
    {
        choice = displayMenu();
            switch (choice)
            {
            case 1: // Добавление элемента
                cout << "Введите значение для добавления: ";
                cin >> value;
                q.queue(value); // Добавление в очередь
                break;
            case 2: // Извлечение элемента
                try
                {
                    cout << "Извлеченный элемент: " << q.unqueue() << endl;
                }
                catch (const out_of_range& e)
                { // Обработка исключения, если очередь пуста
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            case 3: // Подсчет количества элементов
                cout << "Количество элементов: " << q.count() << endl;
                break;
            case 4: // Очистка очереди
                q.clear();
                cout << "Очередь очищена." << endl;
                break;
            case 5: // Вставка 1 перед каждым отрицательным числом
                insertBeforeNegatives(q); // Вызов функции для вставки
                cout << "1 вставлена перед каждым отрицательным числом." << endl;
                break;
            case 6: // Удаление всех отрицательных элементов
                removeNegatives(q); // Вызов функции для удаления
                cout << "Все отрицательные элементы удалены." << endl;
                break;
            case 7: // Подсчет количества вхождений заданного значения
                cout << "Введите значение для подсчета: ";
                cin >> value;
                cout << "Количество вхождений " << value << ": " << countOccurrences(q, value) << endl;
                break;
            case 8: // Вывод очереди
                printQueue(q); // Вызов функции для вывода элементов очереди
                break;
            case 0: // Выход из программы
                cout << "Выход из программы." << endl;
                break;
            default: // Обработка неверного выбора
                cout << "Неверный выбор. Попробуйте снова." << endl;
            }
    } while (choice != 0);

    return 0;
}