#include "HMArray.h"
#pragma once
#include <algorithm>
#include <cassert>

namespace HARMONY
{
    template<typename T>
    inline HMArray<T>::HMArray() : data(nullptr), capacity(0), size(0)
    {

    }

    template<typename T>
    inline HMArray<T>::HMArray(std::initializer_list<value_type> init) : size(init.size()), capacity(init.size())
    {
        data = static_cast<value_type*>(GC_MALLOC(sizeof(value_type) * capacity));
        std::copy(init.begin(), init.end(), data);    
    }

    template<typename T>
    inline HMArray<T>::HMArray(size_t size) : size(size),capacity(size)
    {
        data = static_cast<value_type*>(GC_MALLOC(sizeof(value_type) * capacity));
    }
  
    template<typename T>
    inline void HMArray<T>::Add(const value_type& value)
    {
        ensureCapacity(size + 1);
        data[size++] = value;
    }
    template<typename T>
    inline HMArray<T>::value_type* HMArray<T>::GetData()const
    {
        return data;
    }
    template<typename T>
    inline size_t HMArray<T>::GetSize() const
    {
        return size;
    }
    template<typename T>
    inline HMArray<T>::value_type& HMArray<T>::Back()const
    {
        return data[size -1];
    }

    template<typename T>
    inline bool HMArray<T>::isEmpty()const noexcept
    {
        return size == 0 ? true : false;
    }

    template<typename T>
    inline HMArray<T>::value_type& HMArray<T>::operator[](size_t size) const
    {
        if (capacity >= size)
        {
            return data[size];
        }
        assert(false);
    }

    template<typename T>
    HMArray<T>::iterator HMArray<T>::begin()
    {
        return data;
    }
    template<typename T>
    inline HMArray<T>::iterator HMArray<T>::end()
    {
        return data + size;
    }
    template<typename T>
    inline HMArray<T>::const_iterator HMArray<T>::begin() const
    {
        return data;
    }
    template<typename T>
    inline HMArray<T>::const_iterator HMArray<T>::end() const
    {
        return data + size;
    }

    template<typename T>
    inline void HMArray<T>::ensureCapacity(size_t minCapacity)
    {
        if (minCapacity > capacity) {
            size_t newCapacity = std::max(2 * capacity, minCapacity);
            T* newData = static_cast<T*>(GC_MALLOC(sizeof(T) * newCapacity)); // GC管理下のメモリを確保

            // プレースメントnewを使用してオブジェクトを構築
            for (size_t i = 0; i < size; ++i) {
                new (&newData[i]) T(std::move(data[i])); // ムーブコンストラクタを呼び出す
                data[i].~T(); // 古いオブジェクトのデストラクタを明示的に呼び出す
            }

            // 新しいデータ配列へのポインタを更新
            data = newData;
            capacity = newCapacity;
        }
    }
}