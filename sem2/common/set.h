#pragma once

#include <list>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Set {
private:
    static const int DEFAULT_CAPACITY = 10;
    std::vector<std::list<T>> table;
    int current_size;

    int hash(const T& value) const {
        return std::hash<T>()(value) % table.size();
    }

public:
    /// <summary>
    /// Конструктор по умолчанию.
    /// </summary>
    Set() : table(DEFAULT_CAPACITY), current_size(0) {}

    /// <summary>
    /// Добавление элемента в множество.
    /// </summary>
    /// <param name="value">Элемент, который нужно добавить.</param>
    void add(const T& value) {
        int index = hash(value);
        auto& chain = table[index];

        if (std::find(chain.begin(), chain.end(), value) == chain.end()) {
            chain.push_back(value);
            ++current_size;
        }
    }

    /// <summary>
    /// Удаление элемента из множества.
    /// </summary>
    /// <param name="value">Элемент, который нужно удалить.</param>
    void remove(const T& value) {
        int index = hash(value);
        auto& chain = table[index];

        // Ищем элемент в цепочке
        auto it = std::find(chain.begin(), chain.end(), value);
        if (it != chain.end()) {
            chain.erase(it);
            --current_size;
        }
    }

    /// <summary>
    /// Проверка наличия элемента в множестве.
    /// </summary>
    /// <param name="value">Элемент, наличие которого нужно проверить.</param>
    /// <returns>True, если элемент содержится в множестве, иначе False.</returns>
    bool contains(const T& value) const {
        int index = hash(value);
        const auto& chain = table[index];

        return std::find(chain.begin(), chain.end(), value) != chain.end();
    }

    /// <summary>
    /// Очистка множества от всех элементов.
    /// </summary>
    void clear() {
        for (auto& chain : table) {
            chain.clear();
        }
        current_size = 0;
    }

    /// <summary>
    /// Получение количества элементов в множестве.
    /// </summary>
    /// <returns>Количество элементов в множестве.</returns>
    int count() const {
        return current_size;
    }

    /// <summary>
    /// Преобразование множества в вектор.
    /// </summary>
    /// <returns>Вектор, содержащий все элементы множества.</returns>
    std::vector<T> toList() const {
        std::vector<T> keys;

        for (const auto& chain : table) {
            for (const auto& value : chain) {
                keys.push_back(value);
            }
        }
        return keys;
    }
};