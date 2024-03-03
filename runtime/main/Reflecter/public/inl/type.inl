#pragma once

namespace HARMONY
{
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
	inline type type::GetType()
	{



		return type();
	}


}