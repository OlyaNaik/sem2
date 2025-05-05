#pragma once

#include <stdexcept>

using namespace std;

/// <summary>
/// Класс для реализации стека.
/// </summary>
template <typename T>
class Stack
{
private:
    T* elements;
    int capacity;
    int top;

    void resize(int newCapacity)
    {
        T* newElements = new T[newCapacity];
        for (int i = 0; i < top; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

public:
    /// <summary>
    /// Конструктор по умолчанию.
    /// </summary>
    Stack() : capacity(10), top(0)
    {
        elements = new T[capacity];
    }

    /// <summary>
    /// Деструктор.
    /// </summary>
    ~Stack()
    {
        delete[] elements;
    }

    /// <summary>
    /// Добавление элемента на вершину стека.
    /// </summary>
    /// <param name="value">Элемент, который нужно добавить в стек.</param>
    void push(T value)
    {
        if (top == capacity) {
            resize(capacity * 2);
        }
        elements[top++] = value;
    }

    /// <summary>
    /// Извлечение элемента с вершины стека и возвращение его значения.
    /// </summary>
    /// <returns>Элемент с вершины стека.</returns>
    /// <exception cref="out_of_range">Выбрасывается, если стек пуст.</exception>
    T pop()
    {
        if (top == 0) {
            throw out_of_range("Stack is empty");
        }
        return elements[--top];
    }

    /// <summary>
    /// Возвращение элемента, находящегося на вершине стека.
    /// </summary>
    /// <returns>Элемент с вершины стека.</returns>
    /// <exception cref="out_of_range">Выбрасывается, если стек пуст.</exception>
    T peek()
    {
        if (top == 0) {
            throw out_of_range("Stack is empty");
        }
        return elements[top - 1];
    }

    /// <summary>
    /// Возвращение количества элементов в стеке.
    /// </summary>
    /// <returns>Количество элементов в стеке.</returns>
    int count()
    {
        return top;
    }

    /// <summary>
    /// Удаление всех элементов из стека.
    /// </summary>
    void clear()
    {
        top = 0;
    }
};