#include"type.h"
#pragma once
#include<type_traits>
#include"wrapper_mapper.h"

namespace HARMONY
{
	template<typename T>
	inline type type::Get()
	{
        using namespace DETAIL;
        type_data data = new type_data();
        data->_isValid = true;
        data->_size = sizeof(T);

        // 算術型の場合
        if constexpr (std::is_arithmetic_v<T>) {
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_arithmetic));
        }
        // クラスの場合
        if constexpr (std::is_class_v<T>) {
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_class));
        }
        // 列挙型の場合
        if constexpr (std::is_enum_v<T>) {
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_enum));
        }
        // 配列の場合
        if constexpr (std::is_array_v<T>) {
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_array));
        }
        // ポインタの場合
        if constexpr (std::is_pointer_v<T>) {
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_pointer));
        }
        // 関数ポインタの場合
        if constexpr (std::is_function_v<std::remove_pointer_t<T>>) {
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_function_pointer));
        }
        // メンバオブジェクトポインタの場合
        if constexpr (std::is_member_object_pointer_v<T>) {
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_member_object_pointer));
        }
        // メンバ関数ポインタの場合
        if constexpr (std::is_member_function_pointer_v<T>) {
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_member_function_pointer));
        }
        // ラッパータイプかどうか
        if constexpr (is_wrapper<T>::value){
            data._info.set(static_cast<std::size_t>(type_trait_infos::is_wrappermapper));
        }
		return type(data);
	}
}