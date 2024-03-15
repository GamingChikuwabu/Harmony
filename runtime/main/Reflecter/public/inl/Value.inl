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
			_impl = std::make_shared<ValueImpl<T>>(var); 
		}
		else
		{
			_impl = var._impl;
		}
	}

	template<typename T>
	inline T Value::TryConvert()
	{
		ValueImpl<T>* temp = static_cast<ValueImpl<T>*>(_impl.get());
		return temp->getValue();
	}
}