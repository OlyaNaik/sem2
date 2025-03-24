#pragma once

#include <stdexcept>

template <typename T>
class Stack {
private:
    T* elements;      // Указатель на динамический массив
    int capacity;     // Вместимость стека
    int top;          // Индекс верхнего элемента стека

    // Увеличивает вместимость стека
    void resize(int newCapacity) {
        T* newElements = new T[newCapacity];
        for (int i = 0; i < top; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

public:
    Stack() : capacity(10), top(0) {
        elements = new T[capacity]; // Инициализация динамического массива
    }

    ~Stack() {
        delete[] elements; // Освобождение памяти
    }

    // Добавление элемента на вершину стека
    void push(T value) {
        if (top == capacity) {
            resize(capacity * 2); // Увеличение вместимости при необходимости
        }
        elements[top++] = value;
    }

    // Извлечение элемента с вершины стека и возвращение его значения
    T pop() {
        if (top == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[--top];
    }

    // Возвращение элемента находящегося на вершине стека
    T peek() {
        if (top == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[top - 1];
    }

    // Возвращение количества элементов в коллекции
    int count() {
        return top;
    }

    // Удаление всех элементов из коллекции
    void clear() {
        top = 0; // Сбрасывание индекса верхнего элемента
    }
};