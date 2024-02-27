#include"type.h"
#pragma once
#include<type_traits>
#include"wrapper_mapper.h"
#include"detail/type/type_data.h"
#include"registration.h"

namespace HARMONY
{
    using namespace DETAIL;
    //==================================================================================
    // エイリアス
    //==================================================================================
    template<typename T>
    using is_complete_type = std::integral_constant<bool, !std::is_function<T>::value && !std::is_same<T, void>::value>;

    type DETAIL::CreateType(DETAIL::type_data* _data)
    {
        return _data ? type(_data) : type();
    }

    type DETAIL::GetInvalidType()
    {
        return CreateType(nullptr);
    }
    
    template<typename T>
    inline std::enable_if_t<is_complete_type<T>::value, type> create_or_get_type() noexcept
    {
        using type_must_be_complete = char[sizeof(T) ? 1 : -1];
        (void)sizeof(type_must_be_complete);
        static const type val = CreateType(registration::AddItem(make_type_data<T>()));
        return val;
    }

    template<typename T>
    inline std::enable_if_t<!is_complete_type<T>::value, type> create_or_get_type() noexcept
    {
        static const type val = CreateType(registration::AddItem(make_type_data<T>()));
        return val;
    }

	template<typename T>
	inline type type::Get()
	{
        auto typeData = create_or_get_type<T>()._data;
        return typeData; 
	}

    /// @brief 無効な型を取得する時にのみ行う
    /// @return 
    template<>
    inline type type::Get<DETAIL::invalid_type>()
    {
        return DETAIL::GetInvalidType();
    }
}