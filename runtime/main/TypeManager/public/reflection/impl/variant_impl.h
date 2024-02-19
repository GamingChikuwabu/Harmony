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
}