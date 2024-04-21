#pragma once
#include "gc_cpp.h"
#include "gc/gc_allocator.h"
#include <algorithm> // std::copyを使用
#include <initializer_list> // 初期化リストのサポート

namespace HARMONY
{
	template<typename T>
	class HMArray
	{
    public:
        using value_type = T;
        using iterator = value_type*;
        using const_iterator = const value_type*;
    public:
        HMArray();
        HMArray(std::initializer_list<value_type> init);
        HMArray(size_t size);
        ~HMArray() = default;
    public:
        /// @brief 
        /// @param value 
        void Add(const value_type& value);
        /// @brief 要素数を取得する
        /// @return 要素数
        size_t GetSize() const;
        /// @brief 要素の先頭アドレスを取得する
        /// @return 先頭アドレス
        value_type* GetData()const;
        /// @brief 要素の一番最後の要素を取得する
        /// @return 一番最後の要素
        value_type& Back()const;
        /// @brief 要素が空かを判定する
        /// @return 結果
        bool isEmpty()const noexcept;
        void ReSize(size_t size);
        void Clear();
        void Reserve(size_t capacity);
        void Insert(iterator pos, const value_type& value);
        void Insert(iterator pos, std::initializer_list<value_type> init);
        void Insert(iterator pos, const value_type* first,size_t _size);
        void Sort();
    public:
        value_type& operator[](size_t size)const;
        void operator==(const HMArray& other);
        void operator==(HMArray&& other) noexcept;
    public:
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        iterator erase(iterator pos) {
            // 削除される要素以降の要素を一つ前に移動
            std::move(pos + 1, data + size, pos);
            // 配列のサイズを更新
            --size;
            // 削除した要素の次を指すイテレータを返す
            return pos;
        }
    private:
        value_type* data;
        size_t capacity;
        size_t size;

        void ensureCapacity(size_t minCapacity);
	};
    
}

// デフォルトのメタ関数定義。特定の型にはマッチしない。
template<typename T>
struct is_innertype {
    
};

// HMArrayに対する特殊化。
template<typename T>
struct is_innertype<HARMONY::HMArray<T>> {
    // HMArrayから内部型Tを抜き出す。
    using type = T;
};

#include"detail/HMArray_impl.inl"