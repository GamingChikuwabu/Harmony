#include"HMUnorderedMap.h"
#pragma once

namespace HARMONY
{
    template<typename KeyType, typename ValueType>
    inline HMUnorderedMap<KeyType, ValueType>::HMUnorderedMap(size_t size)
    : bucketCount(size), buckets(size), count(0)
    {
    }

    template<typename KeyType, typename ValueType>
    inline void HMUnorderedMap<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
    {
        size_t bucketIndex = hashFunction(key);
        HMArray<HMPair<KeyType, ValueType>>& bucket = buckets[bucketIndex].entries;
        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        bucket.Add(HMPair<KeyType, ValueType>(key, value));
        count++;
    }

    template<typename KeyType, typename ValueType>
    inline ValueType* HMUnorderedMap<KeyType, ValueType>::search(const KeyType& key)
    {
        size_t bucketIndex = hashFunction(key);
        auto& bucket = buckets[bucketIndex].entries;
        for (auto& entry : bucket) {
            if (entry.first == key) {
                return &entry.second;
            }
        }
        
    }

    template<typename KeyType, typename ValueType>
    ValueType& HMUnorderedMap<KeyType, ValueType>::operator[](const KeyType& key) {
        size_t bucketIndex = hashFunction(key);
        HMArray<HMPair<KeyType, ValueType>>& bucket = buckets[bucketIndex].entries;
        for (auto& entry : bucket) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        // キーが存在しない場合は、新しいエントリを追加
        bucket.Add(HMPair<KeyType, ValueType>(key, ValueType()));
        count++;
        return bucket.Back().second;
    }
}