#include "Value.h"
#pragma once
#include"detail/void_ptr.h"

namespace HARMONY
{
	template<typename T, typename Tp>
	inline Value::Value(T& var)
	:_impl(new ValueImpl(var))
	{
		if constexpr (std::is_same_v<Tp, std::string> || std::is_same_v<std::decay_t<Tp>, char*>)
		{
			_impl->_bit.set(static_cast<uint32_t>(ValueKind::STRING));
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