#pragma once
#include<type_traits>

namespace HARMONY
{
    template<typename T, typename Enable = void>
    struct raw_array_type { using type = std::remove_cv_t<T>; };

    template<typename T>
    struct raw_array_type_impl;

    template<typename T, std::size_t N>
    struct raw_array_type_impl<T[N]> { using type = typename raw_array_type<T>::type; };

    template<typename T>
    struct raw_array_type<T, typename std::enable_if<std::is_array<T>::value>::type>
    {
        using type = typename raw_array_type_impl< std::remove_cv_t<T> >::type;
    };

    template<typename T>
    using raw_array_type_t = typename raw_array_type<T>::type;
}