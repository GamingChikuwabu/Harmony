#pragma once
#include <type_traits>
#include <functional>
#include <tuple>

namespace HARMONY
{
    template<typename T>
    struct is_function_ptr : std::integral_constant<bool, std::is_pointer<T>::value&&
        std::is_function <std::remove_pointer_t<T>>::value >
    {
    };

    template <typename T>
    struct function_traits : function_traits< decltype(&T::operator()) > {};

    template<typename R, typename... Args>
    struct function_traits<R(Args...)>
    {
        static const size_t arg_count = sizeof...(Args);

        using return_type = R;
        using arg_types = std::tuple<Args...>;
    };

    template<typename R, typename... Args>
    struct function_traits<R(*)(Args...)> : function_traits<R(Args...)> { };

    template<typename R, typename... Args>
    struct function_traits<R(&)(Args...)> : function_traits<R(Args...)> { };

    template<typename R, typename C, typename... Args>
    struct function_traits<R(C::*)(Args...)> : function_traits<R(Args...)> { using class_type = C; };

    template<typename R, typename C, typename... Args>
    struct function_traits<R(C::*)(Args...) const> : function_traits<R(Args...)> { using class_type = C; };

    template<typename R, typename C, typename... Args>
    struct function_traits<R(C::*)(Args...) volatile> : function_traits<R(Args...)> { using class_type = C; };

    template<typename R, typename C, typename... Args>
    struct function_traits<R(C::*)(Args...) const volatile> : function_traits<R(Args...)> { using class_type = C; };

    template<typename R, typename... Args>
    struct function_traits<R(*)(Args...) noexcept> : function_traits<R(Args...)> { };

    template<typename R, typename... Args>
    struct function_traits<R(&)(Args...) noexcept> : function_traits<R(Args...)> { };

    template<typename R, typename C, typename... Args>
    struct function_traits<R(C::*)(Args...) noexcept> : function_traits<R(Args...)> { using class_type = C; };

    template<typename R, typename C, typename... Args>
    struct function_traits<R(C::*)(Args...) const noexcept> : function_traits<R(Args...)> { using class_type = C; };

    template<typename R, typename C, typename... Args>
    struct function_traits<R(C::*)(Args...) volatile noexcept> : function_traits<R(Args...)> { using class_type = C; };

    template<typename R, typename C, typename... Args>
    struct function_traits<R(C::*)(Args...) const volatile noexcept> : function_traits<R(Args...)> { using class_type = C; };

    template<typename T>
    struct function_traits<std::function<T>> : function_traits<T> {};

}