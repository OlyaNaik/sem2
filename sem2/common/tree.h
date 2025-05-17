#pragma once

#include <iostream>
#include <vector>

/// <summary>
/// Класс для реализации сбалансированного дерева.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
template <typename T>
class Tree {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        explicit Node(const T& value) : value(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size;
    bool autoBalance;

    // Вспомогательные функции
    void clearRecursive(Node* node);
    bool containsRecursive(Node* node, const T& value) const;
    Node* addRecursive(Node* node, const T& value);
    Node* removeRecursive(Node* node, const T& value);
    Node* findMin(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    void traverseRecursive(Node* node, std::vector<T>& result, int order) const;

public:
    /// <summary>
    /// Типы обхода дерева.
    /// </summary>
    enum Order { Prefix, Infix, Postfix, LevelsUpLeft, LevelsUpRight, LevelsDownLeft, LevelsDownRight };

    /// <summary>
    /// Конструктор дерева.
    /// </summary>
    /// <param name="autoBalance">Флаг автоматического балансирования (по умолчанию false).</param>
    explicit Tree(bool autoBalance = false);

    /// <summary>
    /// Деструктор дерева.
    /// </summary>
    ~Tree();

    void add(T value);
    void remove(T value);
    void clear();
    bool contains(T value) const;
    int count() const;

    std::vector<T> ToList(Order order) const;
    std::vector<T> ToList() const;

    void ToLeft(T value);
    void ToRight(T value);
};

/// <summary>
/// Конструктор дерева.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="autoBalance">Флаг автоматического балансирования дерева.</param>
template <typename T>
Tree<T>::Tree(bool autoBalance) : root(nullptr), size(0), autoBalance(autoBalance) {}

/// <summary>
/// Деструктор дерева. Вызывает очистку всех узлов.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
template <typename T>
Tree<T>::~Tree() {
    clear();
}

/// <summary>
/// Очистка дерева (удаление всех узлов).
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
template <typename T>
void Tree<T>::clear() {
    clearRecursive(root);
    root = nullptr;
    size = 0;
}

/// <summary>
/// Рекурсивная очистка дерева, начиная с указанного узла.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="node">Узел, с которого начинается очистка.</param>
template <typename T>
void Tree<T>::clearRecursive(Node* node) {
    if (node) {
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }
}

/// <summary>
/// Добавление нового элемента в дерево.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="value">Значение для добавления.</param>
template <typename T>
void Tree<T>::add(T value) {
    root = addRecursive(root, value);
    size++;
}

/// <summary>
/// Рекурсивное добавление элемента в дерево.
/// Возвращает указатель на корневой узел после добавления.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="node">Текущий узел, к которому осуществляется добавление.</param>
/// <param name="value">Добавляемое значение.</param>
/// <returns>Указатель на обновлённый узел.</returns>
template <typename T>
typename Tree<T>::Node* Tree<T>::addRecursive(Node* node, const T& value) {
    if (!node) {
        return new Node(value);
    }
    if (value < node->value) {
        node->left = addRecursive(node->left, value);
    }
    else if (value > node->value) {
        node->right = addRecursive(node->right, value);
    }

    return node;
}

/// <summary>
/// Удаление элемента из дерева.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="value">Значение для удаления.</param>
template <typename T>
void Tree<T>::remove(T value) {
    root = removeRecursive(root, value);
}

/// <summary>
/// Рекурсивное удаление элемента из дерева.
/// Возвращает указатель на корневой узел после удаления.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="node">Текущий узел, в котором нужно искать удаляемый элемент.</param>
/// <param name="value">Удаляемое значение.</param>
/// <returns>Указатель на обновлённый узел.</returns>
template <typename T>
typename Tree<T>::Node* Tree<T>::removeRecursive(Node* node, const T& value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = removeRecursive(node->left, value);
    }
    else if (value > node->value) {
        node->right = removeRecursive(node->right, value);
    }
    else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            size--;
            return temp;
        }
        else if (!node->right) {
            Node* temp = node->left;
            delete node;
            size--;
            return temp;
        }

        Node* minNode = findMin(node->right);
        node->value = minNode->value;
        node->right = removeRecursive(node->right, minNode->value);
    }

    return node;
}

/// <summary>
/// Поиск минимального узла в поддереве.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="node">Узел, с которого начинается поиск.</param>
/// <returns>Указатель на узел с минимальным значением.</returns>
template <typename T>
typename Tree<T>::Node* Tree<T>::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

/// <summary>
/// Проверка, содержит ли дерево заданный элемент.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="value">Значение для проверки.</param>
/// <returns>True, если элемент найден; иначе False.</returns>
template <typename T>
bool Tree<T>::contains(T value) const {
    return containsRecursive(root, value);
}

/// <summary>
/// Рекурсивная проверка наличия элемента в дереве.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="node">Текущий узел.</param>
/// <param name="value">Значение для поиска.</param>
/// <returns>True, если элемент найден; иначе False.</returns>
template <typename T>
bool Tree<T>::containsRecursive(Node* node, const T& value) const {
    if (!node) return false;

    if (value == node->value) return true;
    if (value < node->value) return containsRecursive(node->left, value);
    return containsRecursive(node->right, value);
}

/// <summary>
/// Возвращение количества элементов в дереве.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <returns>Количество элементов.</returns>
template <typename T>
int Tree<T>::count() const {
    return size;
}

/// <summary>
/// Преобразование дерева в массив с заданным порядком обхода.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="order">Тип обхода дерева.</param>
/// <returns>Вектор значений дерева.</returns>
template <typename T>
std::vector<T> Tree<T>::ToList(Order order) const {
    std::vector<T> result;
    traverseRecursive(root, result, order);
    return result;
}

/// <summary>
/// Преобразование дерева в массив с использованием обхода Infix.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <returns>Вектор значений дерева.</returns>
template <typename T>
std::vector<T> Tree<T>::ToList() const {
    return ToList(Infix);
}

/// <summary>
/// Рекурсивный обход дерева в заданном порядке и заполнение результирующего вектора.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="node">Текущий узел, который нужно посетить.</param>
/// <param name="result">Вектор для сохранения результата обхода.</param>
/// <param name="order">Тип обхода (Prefix, Infix, Postfix).</param>
template <typename T>
void Tree<T>::traverseRecursive(Node* node, std::vector<T>& result, int order) const {
    if (!node) return;

    if (order == Prefix) {
        result.push_back(node->value);
        traverseRecursive(node->left, result, order);
        traverseRecursive(node->right, result, order);
    }
    else if (order == Infix) {
        traverseRecursive(node->left, result, order);
        result.push_back(node->value);
        traverseRecursive(node->right, result, order);
    }
    else if (order == Postfix) {
        traverseRecursive(node->left, result, order);
        traverseRecursive(node->right, result, order);
        result.push_back(node->value);
    }
}

/// <summary>
/// Выполнение поворота узла дерева влево.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="value">Значение узла для поворота.</param>
template <typename T>
void Tree<T>::ToLeft(T value) {
    Node* node = root;
    while (node && node->value != value) {
        if (value < node->value) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    if (!node || !node->right) return;
    Node* newRoot = rotateLeft(node);
    if (node == root) root = newRoot;
}

/// <summary>
/// Выполнение поворота узла дерева вправо.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="value">Значение узла для поворота.</param>
template <typename T>
void Tree<T>::ToRight(T value) {
    Node* node = root;
    while (node && node->value != value) {
        if (value < node->value) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    if (!node || !node->left) return;
    Node* newRoot = rotateRight(node);
    if (node == root) root = newRoot;
}

/// <summary>
/// Поворот узла и его правого поддерева влево.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="node">Узел, который нужно повернуть.</param>
/// <returns>Новый корень поддерева после поворота.</returns>
template <typename T>
typename Tree<T>::Node* Tree<T>::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

/// <summary>
/// Поворот узла и его левого поддерева вправо.
/// </summary>
/// <typeparam name="T">Тип данных, хранимых в дереве.</typeparam>
/// <param name="node">Узел, который нужно повернуть.</param>
/// <returns>Новый корень поддерева после поворота.</returns>
template <typename T>
typename Tree<T>::Node* Tree<T>::rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}