#pragma once

#include <iostream>
#include <stdexcept>

/// <summary>
/// Класс для реализации циклического списка.
/// </summary>
/// <typeparam name="T">Тип элементов, которые будут храниться в списке.</typeparam>
template<typename T>
class CycleList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    /// <summary>
    /// Конструктор по умолчанию для создания пустого циклического списка.
    /// </summary>
    CycleList() : head(nullptr), size(0) {}

    /// <summary>
    /// Деструктор, который очищает список.
    /// </summary>
    ~CycleList()
    {
        clear();
    }

    /// <summary>
    /// Добавляет элемент в конец списка.
    /// </summary>
    /// <param name="value">Элемент, который нужно добавить в список.</param>
    void add(T value)
    {
        Node* newNode = new Node(value);
        if (!head)
        {
            head = newNode;
            head->next = head; // замыкаем список
        }
        else
        {
            Node* temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        size++;
    }

    /// <summary>
    /// Вставляет элемент по указанному индексу.
    /// </summary>
    /// <param name="index">Индекс, по которому нужно вставить элемент.</param>
    /// <param name="value">Элемент, который нужно вставить в список.</param>
    /// <exception cref="std::out_of_range">Выбрасывается, если индекс вне диапазона.</exception>
    void insert(int index, T value)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Index out of range");
        }
        Node* newNode = new Node(value);
        if (index == 0)
        {
            if (!head)
            {
                head = newNode;
                head->next = head;
            }
            else
            {
                Node* temp = head;
                while (temp->next != head)
                {
                    temp = temp->next;
                }
                newNode->next = head;
                temp->next = newNode;
                head = newNode;
            }
        }
        else
        {
            Node* temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        size++;
    }

    /// <summary>
    /// Удаляет элемент по указанному индексу.
    /// </summary>
    /// <param name="index">Индекс элемента, который нужно удалить.</param>
    /// <exception cref="std::out_of_range">Выбрасывается, если индекс вне диапазона.</exception>
    void removeAt(int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            if (size == 1)
            {
                delete head;
                head = nullptr;
            }
            else
            {
                Node* temp = head;
                while (temp->next != head)
                {
                    temp = temp->next;
                }
                Node* toDelete = head;
                head = head->next;
                temp->next = head;
                delete toDelete;
            }
        }
        else
        {
            Node* temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
        }
        size--;
    }

    /// <summary>
    /// Получает элемент по указанному индексу.
    /// </summary>
    /// <param name="index">Индекс элемента, который нужно получить.</param>
    /// <returns>Элемент по указанному индексу.</returns>
    /// <exception cref="std::out_of_range">Выбрасывается, если индекс вне диапазона.</exception>
    T& operator[](const int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        Node* temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    /// <summary>
    /// Возвращает количество элементов в списке.
    /// </summary>
    /// <returns>Количество элементов в списке.</returns>
    int count() const
    {
        return size;
    }

    /// <summary>
    /// Возвращает количество вхождений указанного элемента в списке.
    /// </summary>
    /// <param name="value">Элемент, количество вхождений которого нужно подсчитать.</param>
    /// <returns>Количество вхождений элемента в списке.</returns>
    int count(T value) const
    {
        int count = 0;
        Node* temp = head;
        if (temp)
        {
            do
            {
                if (temp->data == value)
                {
                    count++;
                }
                temp = temp->next;
            } while (temp != head);
        }
        return count;
    }

    /// <summary>
    /// Очищает список, удаляя все элементы.
    /// </summary>
    void clear()
    {
        if (!head) return;
        Node* current = head;
        Node* nextNode;
        do
        {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
        head = nullptr;
        size = 0;
    }
};