#include"Property/Property.h"
#pragma once

namespace HARMONY
{
	template<typename A>
	inline A Property::GetAccessorPtr()
	{
		return reinterpret_cast<A>(accessor);
	}
}