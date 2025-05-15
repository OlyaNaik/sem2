#include <iostream>
#include "stack.h" // Подключение заголовочного файла стека

using namespace std; // Использование стандартного пространства имен

int main()
{
    setlocale(LC_ALL, "RUS");
    Stack<int> stack;
    int number;

    cout << "Введите последовательность чисел (0 для завершения):" << endl;

    // Чтение чисел, пока не будет введен 0
    while (true) 
    {
        cin >> number;
        if (number == 0) 
        {
            break;
        }
        stack.push(number); // Добавление всех введенных чисел в стек
    }

    cout << "Положительные числа в обратном порядке:" << endl;

    // Извлечение и вывод положительных чисел в обратном порядке
    while (stack.count() > 0) 
    {
        int value = stack.pop();
        if (value > 0) 
        {
            cout << value << endl; // Вывод только положительных чисел
        }
    }

    return 0;
}