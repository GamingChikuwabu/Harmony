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
    inline void HMArray<T>::push_back(const value_type& value)
    {
        ensureCapacity(size + 1);
        data[size++] = value;
    }
    template<typename T>
    inline size_t HMArray<T>::getSize() const
    {
        return size;
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
            value_type* newData = static_cast<value_type*>(GC_MALLOC(sizeof(value_type) * newCapacity));
            std::copy(data, data + size, newData);
            data = newData;
            capacity = newCapacity;
        }
    }
}