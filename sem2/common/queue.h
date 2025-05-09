#pragma once

#include <iostream>
#include <stdexcept>

/// <summary>
/// Класс для реализации очереди.
/// </summary>
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* front = nullptr;
    Node* rear = nullptr;
    int size = 0;

public:
    /// <summary>
    /// Конструктор по умолчанию.
    /// </summary>
    Queue() = default;

    /// <summary>
    /// Деструктор для автоматического освобождения памяти.
    /// </summary>
    ~Queue() {
        clear();
    }

    /// <summary>
    /// Добавляет новый элемент в конец очереди.
    /// </summary>
    /// <param name="value">Элемент, который нужно добавить.</param>
    void queue(T value) {
        Node* newNode = new Node(value);
        if (rear) {
            rear->next = newNode;
        }
        else {
            front = newNode;
        }
        rear = newNode;
        size++;
    }

    /// <summary>
    /// Удаляет и возвращает элемент из начала очереди.
    /// </summary>
    /// <returns>Удалённое значение.</returns>
    /// <exception cref="std::out_of_range">Выбрасывается, если очередь пуста.</exception>
    T unqueue() {
        if (!front) {
            throw std::out_of_range("Queue is empty");
        }
        Node* temp = front;
        T returnValue = front->data;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        delete temp;
        size--;
        return returnValue;
    }

    /// <summary>
    /// Возвращает текущее количество элементов в очереди.
    /// </summary>
    /// <returns>Количество элементов в очереди.</returns>
    int count() const {
        return size;
    }

    /// <summary>
    /// Очищает очередь, удаляя все элементы.
    /// </summary>
    void clear() {
        while (front) {
            unqueue();
        }
    }

    /// <summary>
    /// Проверяет, является ли очередь пустой.
    /// </summary>
    /// <returns>true, если очередь пуста; иначе false.</returns>
    bool isEmpty() const {
        return size == 0;
    }
};