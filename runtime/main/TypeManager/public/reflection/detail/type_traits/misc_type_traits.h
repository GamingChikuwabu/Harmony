#pragma once
#include<type_traits>

namespace HARMONY
{
    class type;
    template<typename T>
    struct associative_container_mapper;
    template<typename T>
    struct sequential_container_mapper;
	namespace DETAIL
	{
        //===================================================================
        // 関数ポインタ特定type_traits
        //===================================================================
        template<typename T>
        struct is_function_ptr : std::integral_constant
            <bool, 
            std::is_pointer<T>::value
            &&std::is_function<std::remove_pointer_t<T>>::value>{};
        //===================================================================
        // rawtype型に変換するtype_traits
        //===================================================================
        template<typename T, typename Enable = void>
        struct raw_type
        {
            using type = std::remove_cv_t<T>;
        };

        template<typename T> 
        struct raw_type<T, std::enable_if_t<std::is_pointer<T>::value && !is_function_ptr<T>::value>>
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

		//===================================================================
		// void*型に変換するtype_traits
		//===================================================================
        template<typename T>
        struct get_ptr_impl
        {
            static inline void* get(T& data)
            {
                return const_cast<void*>(reinterpret_cast<const void*>(&data));
            }
        };

        template<typename T>
        struct get_ptr_impl<T*>
        {
            static inline void* get(T* data)
            {
                return get_ptr_impl<T>::get(*data);
            }
        };

        template<>
        struct get_ptr_impl<void*>
        {
            static inline void* get(void* data)
            {
                return data;
            }
        };

        template<>
        struct get_ptr_impl<const void*>
        {
            static inline void* get(const void* data)
            {
                return const_cast<void*>(data);
            }
        };

        template<typename T>
        static inline void* get_void_ptr(T* data)
        {
            return get_ptr_impl<T*>::get(data);
        }

        template<typename T>
        static inline void* get_void_ptr(T& data)
        {
            return get_ptr_impl<T>::get(data);
        }

        //===================================================================
        // コンテナ型を判別するtype_traits
        //===================================================================
        template <typename T>
        struct has_is_valid_alias
        {
            typedef char YesType[1];
            typedef char NoType[2];

            template <typename U> static YesType& check(typename U::is_valid*);
            template <typename U> static NoType& check(...);


            static const bool value = (sizeof(check<T>(0)) == sizeof(YesType));
        };

        template<typename T, typename Tp = std::remove_cv_t<std::remove_reference_t<T>>>
        using is_associative_container = std::integral_constant<bool, !has_is_valid_alias<associative_container_mapper<Tp>>::value>;
        template<typename T, typename Tp = std::remove_cv_t<std::remove_reference_t<T>>>
        using is_sequential_container = std::integral_constant<bool, !has_is_valid_alias<sequential_container_mapper<Tp>>::value>;
	}
}