#include"variant.h"
#pragma once
#include"type.h"
#include"detail/variant/variant_data.h"
#include"detail/type_traits/misc_type_traits.h"

namespace HARMONY
{
	template<typename T>
	inline variant::variant(T&& obj)
	{
		_data = new DETAIL::variant_data(type::Get<T>(),get_void_ptr(obj));
	}

	template<typename T>
	inline T variant::Convert()const
	{
		return T();
	}
	template<typename T>
	inline bool variant::Convert(T& object) const
	{
		bool re = false;
		const type source_type = GetType();
		const type target_type = type::Get<T>();
		return re;
	}
}