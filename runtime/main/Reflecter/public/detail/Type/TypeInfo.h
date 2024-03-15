#pragma once
#include<bitset>
#include"typetraits.hpp"

namespace HARMONY
{
    namespace DETAIL
    {
        /// @brief 型の種類
        enum class type_trait_infos : size_t
        {
            is_class = 0,
            is_enum,
            is_array,
            is_pointer,
            is_arithmetic,
            is_function_pointer,
            is_member_object_pointer,
            is_member_function_pointer,
            is_associative_container,
            is_sequential_container,
            is_template_instantiation,
            is_wrappermapper,
            TYPE_TRAIT_COUNT
        };

        // access_levelの値の数を取得
        constexpr size_t type_trait_count = static_cast<size_t>(type_trait_infos::TYPE_TRAIT_COUNT);

        using TypeTraitBitSet = std::bitset<type_trait_count>;

        /// @brief 渡された型のビットを立てる
        /// @tparam T 調べる型
        /// @return bit
        template<typename T>
        TypeTraitBitSet GetBitSet()
        {
            std::bitset<type_trait_count> retBit;
            // 算術型の場合
            if constexpr (std::is_arithmetic_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_arithmetic));
            }
            // クラスの場合
            if constexpr (std::is_class_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_class));
            }
            // 列挙型の場合
            if constexpr (std::is_enum_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_enum));
            }
            // 配列の場合
            if constexpr (std::is_array_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_array));
            }
            // ポインタの場合
            if constexpr (std::is_pointer_v<T>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_pointer));
            }
            // 関数ポインタの場合
            if constexpr (std::is_function_v<std::remove_pointer_t<T>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_function_pointer));
            }
            // メンバオブジェクトポインタの場合
            if constexpr (std::is_member_object_pointer_v<T>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_member_object_pointer));
            }
            // メンバ関数ポインタの場合
            if constexpr (std::is_member_function_pointer_v<T>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_member_function_pointer));
            }
            // ラッパータイプかどうか
            if constexpr (is_wrapper<T>::value) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_wrappermapper));
            }
            //// ラッパータイプかどうか
            //if constexpr (is_sequential_container<T>::value) {
            //    retBit.set(static_cast<std::size_t>(type_trait_infos::is_sequential_container));
            //}
            //// ラッパータイプかどうか
            //if constexpr (is_associative_container<T>::value) {
            //    retBit.set(static_cast<std::size_t>(type_trait_infos::is_associative_container));
            //}
            return retBit;
        }
    }
}