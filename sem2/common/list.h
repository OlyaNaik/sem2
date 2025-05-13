#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

/// <summary>
/// Класс для реализации двусвязного списка.
/// </summary>
template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    /// <summary>
    /// Конструктор по умолчанию.
    /// </summary>
    List() : head(nullptr), tail(nullptr), size(0) {}

    /// <summary>
    /// Деструктор, освобождающий память.
    /// </summary>
    ~List()
    {
        clear();
    }

    /// <summary>
    /// Добавление элемента в конец списка.
    /// </summary>
    /// <param name="value">Элемент, который нужно добавить.</param>
    void add(T value)
    {
        Node* newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    /// <summary>
    /// Вставка элемента по указанному индексу.
    /// </summary>
    /// <param name="index">Индекс, по которому нужно вставить элемент.</param>
    /// <param name="value">Элемент, который нужно вставить.</param>
    /// <exception cref="out_of_range">Выбрасывается, если индекс выходит за пределы.</exception>
    void insert(int index, T value)
    {
        if (index < 0 || index > size) throw std::out_of_range("Index out of range");
        Node* newNode = new Node(value);
        if (index == 0)
        {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            if (!tail) tail = newNode;
        }
        else
        {
            Node* current = head;
            for (int i = 0; i < index - 1; i++)
            {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next) current->next->prev = newNode;
            current->next = newNode;
            if (!newNode->next) tail = newNode;
        }
        size++;
    }

    /// <summary>
    /// Удаление элемента по указанному индексу.
    /// </summary>
    /// <param name="index">Индекс элемента для удаления.</param>
    /// <exception cref="out_of_range">Выбрасывается, если индекс выходит за пределы.</exception>
    void removeAt(int index)
    {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");

        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        if (!current) return;

        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (current == head) head = current->next;
        if (current == tail) tail = current->prev;
        delete current;
        size--;
    }

    /// <summary>
    /// Получение элемента по указанному индексу.
    /// </summary>
    /// <param name="index">Индекс элемента.</param>
    /// <returns>Ссылка на элемент.</returns>
    /// <exception cref="out_of_range">Выбрасывается, если индекс выходит за пределы.</exception>
    T& operator[](const int index)
    {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    /// <summary>
    /// Получение количества элементов в списке.
    /// </summary>
    /// <returns>Количество элементов в списке.</returns>
    int count() const
    {
        return size;
    }

    /// <summary>
    /// Подсчет количества вхождений указанного значения в список.
    /// </summary>
    /// <param name="value">Элемент для подсчета.</param>
    /// <returns>Количество вхождений элемента.</returns>
    int count(T value) const
    {
        int count = 0;
        Node* current = head;
        while (current)
        {
            if (current->data == value) count++;
            current = current->next;
        }
        return count;
    }

    /// <summary>
    /// Очистка списка, удаление всех узлов.
    /// </summary>
    void clear()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
};