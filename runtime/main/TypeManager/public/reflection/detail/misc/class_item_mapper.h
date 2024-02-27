#pragma once
#include<type_traits>

namespace HARMONY
{
	class property;
	class method;
	class constructor;
	class enumeration;
	class destructor;
	namespace DETAIL
	{
        class property_wrapper_base;
        class method_wrapper_base;
        class constructor_wrapper_base;
        class destructor_wrapper_base;
        class enumeration_wrapper_base;

        template<typename T>
        using class_item_to_wrapper_t = std::conditional_t< std::is_same<T, property>::value,
            property_wrapper_base,
            std::conditional_t< std::is_same<T, method>::value,
            method_wrapper_base,
            std::conditional_t< std::is_same<T, constructor>::value,
            constructor_wrapper_base,
            std::conditional_t< std::is_same<T, destructor>::value,
            destructor_wrapper_base,
            std::conditional_t< std::is_same<T, enumeration>::value,
            enumeration_wrapper_base,
            void>
            >
            >
            >
        >;


        template<typename T>
        T create_item(const class_item_to_wrapper_t<T>* wrapper);

        template<typename T>
        T create_invalid_item();
	}
}
