#pragma once
//#include"Types/variant.h"
#include"ItemCreator.h"

namespace HARMONY
{
	template<typename T>
	inline variant::variant(T& arg)
	{
		_data = std::make_shared<variant_data>();
		if constexpr (std::is_arithmetic<T>::value)
		{
			Type type = Type::FindByType<T>();
			_data->_type = type;
			_data->_value = arg;
		}
	}

	template<typename T>
	inline T variant::convert() const
	{
		_data-
		return T();
	}
}