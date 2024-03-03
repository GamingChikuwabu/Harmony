#pragma once
#include <type_traits>
#include <memory>


namespace HARMONY
{
    class type;
    template<typename T>
    struct wrapper_mapper<std::shared_ptr<T>> 
    {
        using wrapped_type = decltype(std::shared_ptr<T>().get());
        using type = std::shared_ptr<T>;

        static wrapped_type get(const type& obj)
        {
            return obj.get();
        }

        static type create(const wrapped_type& t)
        {
            return type(t);
        }
    };

    template<typename T>
    struct wrapper_mapper<std::reference_wrapper<T>>
    {
        using wrapped_type = decltype(std::declval<std::reference_wrapper<T>>().get());
        using type = std::reference_wrapper<T>;

        static wrapped_type get(const type& obj)
        {
            return obj.get();
        }

        static  type create(const wrapped_type& t)
        {
            return type(t);
        }
    };

    template<typename T>
    struct wrapper_mapper<std::unique_ptr<T>>
    {
        using wrapped_type = decltype(std::declval<std::unique_ptr<T>>().get());
        using type = std::unique_ptr<T>;

        static  wrapped_type get(const type& obj)
        {
            return obj.get();
        }

        static  type create(const wrapped_type& t)
        {
            return type(t);
        }
    };

    template<typename T>
    struct wrapper_mapper<std::weak_ptr<T>>
    {
        using wrapped_type = decltype(std::declval<std::weak_ptr<T>>().lock().get());
        using type = std::weak_ptr<T>;

        static wrapped_type get(const type& obj)
        {
            return obj.lock().get();
        }
    };

    namespace DETAIL
    {
        template<typename T>
        using wrapper_mapper_t = typename wrapper_mapper<typename std::remove_cv<typename std::remove_reference<T>::type
        >::type>::wrapped_type;

        template<typename T>
        using is_wrapper = std::integral_constant<bool, !std::is_same<invalid_wrapper_type, wrapper_mapper_t<T>>::value >;
    }
}