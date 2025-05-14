#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>

/// <summary>
/// Класс для реализации словаря (ассоциативного массива).
/// </summary>
/// <typeparam name="K">Тип ключа.</typeparam>
/// <typeparam name="V">Тип значения.</typeparam>
template <typename K, typename V>
class Dictionary 
{
private:
    struct KeyValuePair 
    {
        K key;
        V value;
    };

    std::vector<std::list<KeyValuePair>> table;
    int capacity;
    int size;

    int hashFunction(K key) 
    {
        std::hash<K> hashFn;
        return hashFn(key) % capacity;
    }

public:
    /// <summary>
    /// Конструктор с заданной вместимостью.
    /// </summary>
    /// <param name="capacity">Вместимость словаря (по умолчанию 10).</param>
    Dictionary(int capacity = 10) : capacity(capacity), size(0) 
    {
        table.resize(capacity);
    }

    /// <summary>
    /// Добавление пары ключ-значение в словарь.
    /// </summary>
    /// <param name="key">Ключ для добавления.</param>
    /// <param name="value">Значение для добавления.</param>
    void add(K key, V value) 
    {
        int index = hashFunction(key);
        for (auto& pair : table[index]) 
        {
            if (pair.key == key) 
            {
                pair.value = value;
                return;
            }
        }
        table[index].push_back({ key, value });
        size++;
    }

    /// <summary>
    /// Попытка получить значение по ключу.
    /// </summary>
    /// <param name="key">Ключ для поиска.</param>
    /// <param name="value">Ссылка на значение, которое будет заполнено, если ключ найден.</param>
    /// <returns>True, если ключ найден; иначе false.</returns>
    bool TryGetValue(K key, V& value) 
    {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) 
        {
            if (pair.key == key) 
            {
                value = pair.value;
                return true;
            }
        }
        return false;
    }

    /// <summary>
    /// Удаление пары по ключу.
    /// </summary>
    /// <param name="key">Ключ для удаления.</param>
    void remove(K key) 
    {
        int index = hashFunction(key);
        auto& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) 
        {
            if (it->key == key) 
            {
                chain.erase(it);
                size--;
                return;
            }
        }
    }

    /// <summary>
    /// Получение всех ключей в словаре.
    /// </summary>
    /// <returns>Вектор ключей.</returns>
    std::vector<K> GetKeys() 
    {
        std::vector<K> keys;
        for (const auto& chain : table) 
        {
            for (const auto& pair : chain) 
            {
                keys.push_back(pair.key);
            }
        }
        return keys;
    }

    /// <summary>
    /// Получение всех значений в словаре.
    /// </summary>
    /// <returns>Вектор значений.</returns>
    std::vector<V> GetValues() 
    {
        std::vector<V> values;
        for (const auto& chain : table) 
        {
            for (const auto& pair : chain) 
            {
                values.push_back(pair.value);
            }
        }
        return values;
    }

    /// <summary>
    /// Очистка словаря.
    /// </summary>
    void clear() 
    {
        for (auto& chain : table) 
        {
            chain.clear();
        }
        size = 0;
    }

    /// <summary>
    /// Получение текущего размера словаря.
    /// </summary>
    /// <returns>Количество элементов в словаре.</returns>
    int getSize() const 
    {
        return size;
    }
};