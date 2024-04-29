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
        /**
         * @brief 要素を追加します。
         * @param value 追加する要素
         */
        void Add(const value_type& value);

        /**
         * @brief 要素を追加します。
         * @param value 追加する要素
         */
        void Add(const value_type* ptr, size_t size);

        /**
         * @brief 要素数を取得します。
         * @return 要素数
         */
        size_t GetSize() const;

        /**
         * @brief 要素の先頭アドレスを取得します。
         * @return 先頭アドレス
         */
        value_type* GetData() const;

        /**
         * @brief 要素の一番最後の要素を取得します。
         * @return 一番最後の要素
         */
        value_type& Back() const;

        /**
         * @brief 要素が空かどうかを判定します。
         * @return 結果
         */
        bool isEmpty() const noexcept;

        /**
         * @brief サイズを変更します。
         * @param size 新しいサイズ
         */
        void ReSize(size_t size);

        /**
         * @brief 要素をクリアします。
         */
        void Clear();

        /**
         * @brief 容量を予約します。
         * @param capacity 予約する容量
         */
        void Reserve(size_t capacity);

        /**
         * @brief 指定した位置に要素を挿入します。
         * @param pos 挿入する位置のイテレータ
         * @param value 挿入する要素
         */
        void Insert(iterator pos, const value_type& value);

        /**
         * @brief 指定した位置に初期化リストの要素を挿入します。
         * @param pos 挿入する位置のイテレータ
         * @param init 挿入する初期化リスト
         */
        void Insert(iterator pos, std::initializer_list<value_type> init);

        /**
         * @brief 指定した位置に配列の要素を挿入します。
         * @param pos 挿入する位置のイテレータ
         * @param first 挿入する配列の先頭ポインタ
         * @param _size 挿入する配列の要素数
         */
        void Insert(iterator pos, const value_type* first, size_t _size);

        /**
         * @brief 要素をソートします。
         */
        void Sort();
    public:
        value_type& operator[](size_t size)const;
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