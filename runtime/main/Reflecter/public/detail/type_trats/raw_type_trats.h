#pragma once
#include<type_traits>

namespace HARMONY
{
    namespace DETAIL
    {
        //===================================================================
        // rawtype型に変換するtype_traits
        //===================================================================
        template<typename T, typename Enable = void>
        struct raw_type
        {
            using type = std::remove_cv_t<T>;
        };

        template<typename T>
        struct raw_type<T, std::enable_if_t<std::is_pointer<T>::value && !std::integral_constant
            <bool,
            std::is_pointer<T>::value
            && std::is_function<std::remove_pointer_t<T>>::value>::value>>
        {
            using type = typename raw_type<std::remove_pointer_t<T>>::type;
        };

        template<typename T>
        struct raw_type<T, std::enable_if_t<std::is_reference<T>::value> >
        {
            using type = typename raw_type<std::remove_reference_t<T>>::type;
        };

        template<typename T>
        using raw_type_t = typename raw_type<T>::type;
    }
}