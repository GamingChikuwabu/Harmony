#pragma once
#include"HMArray.h"
#include"HMPair.h"
#include"HMString.h"
#include <functional>

namespace std {
    template <>
    struct hash<HARMONY::HMString> {
        std::size_t operator()(const HARMONY::HMString& key) const {
#ifdef UNICODE
            std::wstring str(key.GetRaw());
            return std::hash<std::wstring>()(str);
#else
            std::string str(key.GetRaw());
            return std::hash<std::string>()(str);
#endif // UNICODE
        }
    };
}

namespace HARMONY
{
	template<typename KeyType, typename ValueType>
	class HMUnorderedMap
	{
    public:
        HMUnorderedMap(size_t size = 101);
        void insert(const KeyType& key, const ValueType& value);
        ValueType* search(const KeyType& key);
        ValueType& operator[](const KeyType& key);
        class iterator {
        private:
            HMUnorderedMap<KeyType, ValueType>* map;
            size_t bucketIndex;
            typename HMArray<HMPair<KeyType, ValueType>>::iterator entryIterator;
        public:
            iterator(HMUnorderedMap<KeyType, ValueType>* map, size_t bucketIndex, typename HMArray<HMPair<KeyType, ValueType>>::iterator entryIt)
                : map(map), bucketIndex(bucketIndex), entryIterator(entryIt) {}
            // デリファレンス演算子
            HMPair<KeyType, ValueType>& operator*() const {
                return *entryIterator;
            }

            // インクリメント演算子 (前置)
            iterator& operator++() {
                ++entryIterator;
                if (entryIterator == map->buckets[bucketIndex].entries.end()) {
                    // 現在のバケットの終わりに達した場合、次の非空のバケットを探す
                    ++bucketIndex;
                    while (bucketIndex < map->bucketCount && map->buckets[bucketIndex].entries.isEmpty()) {
                        ++bucketIndex;
                    }
                    if (bucketIndex < map->bucketCount) {
                        entryIterator = map->buckets[bucketIndex].entries.begin();
                    }
                    else {
                        // コンテナの終わりに達した
                        *this = map->end();
                    }
                }
                return *this;
            }

            // 等価演算子
            bool operator==(const iterator& other) const {
                return bucketIndex == other.bucketIndex && (bucketIndex == map->bucketCount || entryIterator == other.entryIterator);
            }

            // 不等価演算子
            bool operator!=(const iterator& other) const {
                return !(*this == other);
            }

            HMPair<KeyType, ValueType>* operator->() const {
                return &(*entryIterator);
            }
        };

        iterator find(const KeyType& key) {
            size_t bucketIndex = hashFunction(key); // キーからバケットインデックスを計算
            auto& entries = buckets[bucketIndex].entries;
            for (auto it = entries.begin(); it != entries.end(); ++it) {
                if (it->first == key) {
                    // キーが見つかった場合
                    return iterator(this, bucketIndex, it);
                }
            }
            // キーが見つからなかった場合
            return end();
        }

        iterator begin() {
            for (size_t i = 0; i < bucketCount; ++i) {
                if (!buckets[i].entries.isEmpty()) {
                    return iterator(this, i, buckets[i].entries.begin());
                }
            }
            return end();
        }

        iterator end() {
            return iterator(this, bucketCount, {}); // 終端イテレータ
        }

    private:
        struct Bucket {
            HMArray<HMPair<KeyType, ValueType>> entries;
        };
        HMArray<Bucket> buckets;
        size_t bucketCount;
        size_t count;
        size_t hashFunction(const KeyType& key) const {
            return std::hash<KeyType>{}(key) % bucketCount;
        }
	};
    
}

#include"deteil/HMUnorderedMap_impl.inl"