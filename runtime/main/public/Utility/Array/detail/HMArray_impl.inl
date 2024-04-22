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
        return data[0];
    }

    template<typename T>
    inline void HMArray<T>::operator==(const HMArray& other)
    {
    }

    template<typename T>
    inline void HMArray<T>::operator==(HMArray&& other) noexcept
    {

    }

    template<typename T>
    inline void HMArray<T>::ReSize(size_t size)
    {
        ensureCapacity(size);
    }

    template<typename T>
    inline void HMArray<T>::Clear()
    {
        for (size_t i = 0; i < size; ++i) {
			data[i].~T();
		}
		size = 0;
    }

    template<typename T>
    inline void HMArray<T>::Reserve(size_t capacity)
    {
        ensureCapacity(capacity);
    }

    template<typename T>
    inline void HMArray<T>::Insert(iterator pos, const value_type& value)
    {
        Insert(pos, &value, sizeof(value_type));
    }

    template<typename T>
    inline void HMArray<T>::Insert(iterator pos, std::initializer_list<value_type> init)
    {
        ensureCapacity(size + init.size());
		std::move_backward(pos, data + size, data + size + init.size());
		std::copy(init.begin(), init.end(), pos);
		size += init.size();
    }

    template<typename T>
    inline void HMArray<T>::Insert(iterator pos, const value_type* first, size_t _size)
    {
        ensureCapacity(_size);
        std::move_backward(end(), data + size, data + size + _size);
        std::copy(first, first + _size, pos);
        size += _size;
    }

    template<typename T>
    inline void HMArray<T>::Sort()
    {
        std::sort(data, data + size);
    }

    template<typename T>
    inline void HMArray<T>::Add(const value_type* ptr, size_t size)
    {
        // 現在の要素数と追加する要素数を合計した新しいサイズを計算
        size_t newSize = size + this->size;

        // 新しいサイズに合わせて容量を確保
        ensureCapacity(newSize);

        // ポインタから要素をコピーして追加
        std::copy(ptr, ptr + size, data + this->size);

        // サイズを更新
        this->size = newSize;
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

// Path: main/public/Utility/Map/HMUnorderedMap.h