#pragma once
#include<type_traits>

namespace HARMONY
{
	namespace DETAIL
	{
        struct member_func_ptr
        {
            using type = member_func_ptr;
        };

        struct function_ptr
        {
            using type = function_ptr;
        };

        struct member_object_ptr
        {
            using type = member_object_ptr;
        };

        struct object_ptr
        {
            using type = object_ptr;
        };

        template<typename T>
        struct property_type : std::conditional_t< std::is_member_function_pointer<T>::value,
            member_func_ptr,
            std::conditional_t< std::is_member_object_pointer<T>::value,
            member_object_ptr,
            std::conditional_t< std::is_pointer<T>::value,
            object_ptr,
            void
            >>>
        {
        };
	}
}

