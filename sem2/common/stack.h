#pragma once

#include <stdexcept>

template <typename T>
class Stack {
private:
    T* elements;      // ��������� �� ������������ ������
    int capacity;     // ����������� �����
    int top;          // ������ �������� �������� �����

    // ����������� ����������� �����
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
        elements = new T[capacity]; // ������������� ������������� �������
    }

    ~Stack() {
        delete[] elements; // ������������ ������
    }

    // ���������� �������� �� ������� �����
    void push(T value) {
        if (top == capacity) {
            resize(capacity * 2); // ���������� ����������� ��� �������������
        }
        elements[top++] = value;
    }

    // ���������� �������� � ������� ����� � ����������� ��� ��������
    T pop() {
        if (top == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[--top];
    }

    // ����������� �������� ������������ �� ������� �����
    T peek() {
        if (top == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[top - 1];
    }

    // ����������� ���������� ��������� � ���������
    int count() {
        return top;
    }

    // �������� ���� ��������� �� ���������
    void clear() {
        top = 0; // ����������� ������� �������� ��������
    }
};