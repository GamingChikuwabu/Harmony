#include"variant.h"
#pragma once
#include"type.h"
#include"detail/variant_data.h"
#include"detail/misc_type_traits.h"

namespace HARMONY
{
	template<typename T>
	inline variant::variant(T&& obj)
	{
		_data = new DETAIL::variant_data(type::Get<T>());
		_data->_typeAdder = DETAIL::get_void_ptr(obj);
	}

	template<typename T>
	inline T variant::Convert()const
	{
		return Convert_imple<T>();
	}
	template<typename T>
	inline bool variant::Convert(T& object) const
	{
		bool re = false;
		const type source_type = GetType();
		const type target_type = type::Get<T>();


		return re;
	}
	template<typename T>
	inline std::enable_if_t<std::is_arithmetic_v<T>, T> variant::Convert_imple()const
	{
		return (*reinterpret_cast<T*>(_data->_typeAdder));
	}
	template<typename T>
	inline std::enable_if_t<!std::is_arithmetic_v<T>, T> variant::Convert_imple()const
	{
		if constexpr (std::is_pointer<T>::value)
		{
			return reinterpret_cast<T>(_data->_typeAdder);
		}
	}
}