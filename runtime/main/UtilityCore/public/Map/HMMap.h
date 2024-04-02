#pragma once
#ifdef USE_STL 
#include <unordered_map>
template<typename KeyType, typename ValueType>
using HMUnorderedMap = std::unordered_map<KeyType, ValueType>;
#else
#include <vector>
#include <list>
#include <utility>
#include <stdexcept>
#include <algorithm> // find_ifなどのアルゴリズム関数に必要

//namespace HARMONY 
//{
//    template<typename KeyType, typename ValueType>
//    class HMUserMap {
//    public:
//        HMUserMap(size_t size = 101);
//
//        std::pair<typename std::list<std::pair<KeyType, ValueType>>::iterator, bool> insert(const std::pair<KeyType, ValueType>& value);
//
//        // std::mapと同様のeraseメソッド
//        size_t erase(const KeyType& key);
//
//        // std::mapと同様のfindメソッド
//        typename std::list<std::pair<KeyType, ValueType>>::iterator find(const KeyType& key);
//
//        // operator[]の実装は変わらない
//        ValueType& operator[](const KeyType& key);
//
//    private:
//        std::vector<std::list<std::pair<KeyType, ValueType>>> table;
//        size_t tableSize;
//
//        size_t hashFunction(const KeyType& key) const {
//            return std::hash<KeyType>{}(key) % tableSize;
//        }
//    };
//}
//
//template<typename KeyType, typename ValueType>
//using HMUnorderedMap = HARMONY::HMUserMap<KeyType, ValueType>;
//#include "detail/HMMap_impl.inl"
#endif // USE_STL
//#include<unorderd_map>