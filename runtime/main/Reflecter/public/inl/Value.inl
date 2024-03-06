#include "Value.h"
#pragma once

namespace HARMONY
{
	template<typename T, typename Tp>
	inline Value::Value(T&& var)
	{
	}
	template<typename T>
	inline T Value::TryConvert()
	{
		return T();
	}
}