#include "type.h"
#pragma once

namespace HARMONY
{
	template<typename T>
	inline type type::get()
	{
		return type();
	}
	template<typename T>
	inline type HARMONY::type::get(T&& object)
	{
		return type();
	}
	template<typename ...Args>
	inline variant type::Create(Args ...arg)
	{
		return variant();
	}
}