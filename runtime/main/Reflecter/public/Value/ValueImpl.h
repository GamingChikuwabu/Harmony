#pragma once
#include<typeindex>
#include<bitset>
#include<type_traits>
#include <new> 
#include"detail/void_ptr.h"

namespace HARMONY
{
	enum class ValueKind
	{
		ARITHMETIC,
		SEQUENTIAL_ARRAY,
		ASSOCIATIVE_CONTAINER,
		WRAPPED,
		POINTER,
		STRING,
		MAX
	};

    struct ValueImplBase
    {
        virtual ~ValueImplBase() {};
    };

    template<typename T,typename Tp = std::remove_cvref_t<T>>
    struct ValueImpl : public ValueImplBase {
        std::aligned_storage_t<sizeof(T), alignof(T)> storage; // T型のオブジェクトを格納するためのストレージ
        const std::type_info& typeIndex;                       // 格納されているオブジェクトのTypeID
        std::bitset<static_cast<size_t>(ValueKind::MAX)> bit;  // 格納されているオブジェクトの型情報
        bool empty = true; // ストレージが空かどうかを示すフラグ

        // コンストラクタ
        template<typename U>
        ValueImpl(U&& value) : typeIndex(typeid(T)), empty(false) {
            new (&storage) T(std::forward<U>(value));
        }

        // デストラクタ
        ~ValueImpl() {
            if (!empty) {
                
                reinterpret_cast<T*>(&storage)->~T();
            }
        }

        // 格納されているオブジェクトへのポインタを取得
        T* get() {
            return empty ? nullptr : reinterpret_cast<T*>(&storage);
        }

        // 格納されているオブジェクトへのconstポインタを取得
        const T* get() const {
            return empty ? nullptr : reinterpret_cast<const T*>(&storage);
        }

        // 格納されているオブジェクトの値を取得
        T getValue() const {
            return empty ? T() : *reinterpret_cast<const T*>(&storage);
        }

        // ストレージが空かどうかを確認
        bool isEmpty() const {
            return empty;
        }
    };
}