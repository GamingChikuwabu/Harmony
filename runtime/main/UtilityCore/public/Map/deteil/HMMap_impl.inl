#include"Map/HMMap.h"
#pragma once
namespace HARMONY
{
    template<typename KeyType, typename ValueType>
    inline HMUserMap<KeyType, ValueType>::HMUserMap(size_t size)
    {

    }
    template<typename KeyType, typename ValueType>
    inline std::pair<typename std::list<std::pair<KeyType, ValueType>>::iterator, bool> 
        HMUserMap<KeyType, ValueType>::insert(const std::pair<KeyType, ValueType>& value)
    {
        size_t index = hashFunction(value.first);
        auto& list = table[index];

        auto it = std::find_if(list.begin(), list.end(), [&value](const std::pair<KeyType, ValueType>& element) {
            return element.first == value.first;
        });

        if (it != list.end()) {
            return std::make_pair(it, false); // 既に存在する
        }

        list.push_back(value);
        return std::make_pair(--list.end(), true); // 新規挿入
    }
    template<typename KeyType, typename ValueType>
    inline size_t HMUserMap<KeyType, ValueType>::erase(const KeyType& key)
    {
        size_t index = hashFunction(key);
        auto& list = table[index];

        auto it = std::find_if(list.begin(), list.end(), [&key](const std::pair<KeyType, ValueType>& element) {
            return element.first == key;
        });

        if (it != list.end()) {
            list.erase(it);
            return 1; // 削除成功
        }

        return 0; // 要素が見つからない
    }
    template<typename KeyType, typename ValueType>
    inline typename std::list<std::pair<KeyType, ValueType>>::iterator HMUserMap<KeyType, ValueType>::find(const KeyType& key)
    {
        size_t index = hashFunction(key);
        auto& list = table[index];

        return std::find_if(list.begin(), list.end(), [&key](const std::pair<KeyType, ValueType>& element) {
            return element.first == key;
        });
    }
    template<typename KeyType, typename ValueType>
    inline ValueType& HMUserMap<KeyType, ValueType>::operator[](const KeyType& key)
    {
        size_t index = hashFunction(key);
        auto& list = table[index];

        for (auto& pair : list) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        // キーが見つからない場合、新たにデフォルト値を挿入
        list.push_back(std::make_pair(key, ValueType()));
        return list.back().second;
    }
}