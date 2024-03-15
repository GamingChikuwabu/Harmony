#include "Value.h"
#pragma once
#include"detail/void_ptr.h"
#include"Value/ValueImpl.h"
#include"detail/rawtype.h"

namespace HARMONY
{
	template<typename T>
	inline Value::Value(T&& var)
	{
		if constexpr (!std::is_same_v<Value, DETAIL::raw_type_t<T>>)
		{
			_impl = std::make_unique<ValueImpl>(var); 
		}
		else
		{
			_impl = var._impl;
		}
	}

	template<typename T>
	inline T Value::TryConvert()
	{
		if (_impl->_bit.test(static_cast<uint32_t>(ValueKind::STRING)))
		{
			return *reinterpret_cast<T*>(_impl->_ptr);
		}
		return T();
	}
}