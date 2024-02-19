#include"variant.h"
#pragma once
#include"type.h"
#include"detail/variant_data.h"

namespace HARMONY
{
	template<typename T>
	inline variant::variant(T&& obj)
	{
		_data = new DETAIL::variant_data(type::Get<T>());
	}
	template<typename T>
	inline variant::variant(T& obj)
	{
		_data = new DETAIL::variant_data(type::Get<T>());
	}
	template<typename T>
	inline T variant::Convert()
	{
		if (_data->_type == type::Get<T>())
		{
			//static_cast<T>(_data->_typeAdder);
		}
		return T();
	}
}