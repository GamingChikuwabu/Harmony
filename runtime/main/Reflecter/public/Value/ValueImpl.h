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
    struct ValueImpl {
        // ストレージのサイズとアライメントを定義
        static constexpr size_t StorageSize = 64; // 必要に応じてサイズを調整
        static constexpr size_t StorageAlign = alignof(std::max_align_t);

        // std::aligned_storageを使用してストレージを定義
        typename std::aligned_storage<StorageSize, StorageAlign>::type storage;
        std::type_index typeIndex;
        std::bitset<static_cast<size_t>(ValueKind::MAX)> bit;

        template<typename T>
        ValueImpl(T&& value) : typeIndex(typeid(T)) {
            static_assert(sizeof(T) <= StorageSize, "Type is too large for storage");
            static_assert(alignof(T) <= StorageAlign, "Type requires stricter alignment than storage provides");
            // プレースメント newを使用してvalueをstorageにコピー
            new (&storage) T(std::forward<T>(value));

            // 特定の型の場合のフラグ設定
            if constexpr (std::is_same_v<std::decay_t<T>, std::string> ||
                          std::is_same_v<std::decay_t<T>, const char*>) {
                bit.set(static_cast<size_t>(ValueKind::STRING));
            }
        }

        ~ValueImpl() {
            // typeIndexを使用して、適切な型のデストラクタを呼び出す
            if (typeIndex == typeid(std::string)) {
                std::destroy_at(reinterpret_cast<std::string*>(&storage));
            }
            // 他の型に対する破棄処理をここに追加
        }

        // コピー操作やムーブ操作に関する定義が必要になる場合がある
        // （デフォルトのコピー/ムーブコンストラクタ/代入演算子は避けるべき）
        ValueImpl(const ValueImpl&) = delete;
        ValueImpl& operator=(const ValueImpl&) = delete;
    };
}