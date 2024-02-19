#include"type.h"
#pragma once
#include<type_traits>
#include"wrapper_mapper.h"
#include"detail/type_data.h"

namespace HARMONY
{
    using namespace DETAIL;
	template<typename T>
	inline type type::Get()
	{
        type_data* data = new type_data();
        data->_rawType = type::Get<std::remove_cv_t<std::remove_pointer_t<T>>>()._data;
        data->_isValid = true;
        data->_size = sizeof(T); 
        data->_name = typeid(T).name();

        // 算術型の場合
        if constexpr (std::is_arithmetic_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_arithmetic));
        }
        // クラスの場合
        if constexpr (std::is_class_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_class));
        }
        // 列挙型の場合
        if constexpr (std::is_enum_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_enum));
        }
        // 配列の場合
        if constexpr (std::is_array_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_array));
        }
        // ポインタの場合
        if constexpr (std::is_pointer_v<T>) {
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_pointer));
        }
        // 関数ポインタの場合
        if constexpr (std::is_function_v<std::remove_pointer_t<T>>) {
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_function_pointer));
        }
        // メンバオブジェクトポインタの場合
        if constexpr (std::is_member_object_pointer_v<T>) {
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_member_object_pointer));
        }
        // メンバ関数ポインタの場合
        if constexpr (std::is_member_function_pointer_v<T>) {
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_member_function_pointer));
        }
        // ラッパータイプかどうか
        if constexpr (is_wrapper<T>::value){
            data->_wrappedType = type::Get<wrapper_mapper_t<T>>()._data;
            data->_info.set(static_cast<std::size_t>(type_trait_infos::is_wrappermapper));
        }
		return type(data);
	}
}