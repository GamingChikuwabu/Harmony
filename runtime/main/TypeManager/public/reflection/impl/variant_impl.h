#include "variant.h"
#pragma once
#include<type_traits>
#include"detail/data_address_container.h"

namespace HARMONY
{
	template<typename T>
	inline variant::variant(T& obj)
	{

	}
	template<typename T>
	inline T HARMONY::variant::GetValue()
	{
		return Convert<T>();
	}
	template<typename T>
	inline T variant::Convert()const
	{
		return T();
	}
	template<typename T>
	inline bool variant::Convert(T& refObj) const
	{
		return false;
	}
	template<typename T>
	inline bool variant::CanConvert() const
	{
		return false;
	}
}