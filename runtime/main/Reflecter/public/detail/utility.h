#pragma once
#include<type_traits>

namespace HARMONY
{
	namespace DETEIL
	{
        template<typename T, typename Enable = void>
        struct remove_pointers_except_one { using type = T; };
        template<typename T>
        struct remove_pointers_except_one<T, enable_if_t<std::is_pointer<T>::value>>
        {
            using type = conditional_t< std::is_pointer< remove_pointer_t<T> >::value,
                typename remove_pointers_except_one<remove_pointer_t<T>>::type,
                T
            >;
        };
        template<typename T>
        using remove_pointers_except_one_t = typename remove_pointers_except_one<T>::type;
	}
}