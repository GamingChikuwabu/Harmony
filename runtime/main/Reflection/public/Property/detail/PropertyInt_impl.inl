#include"Property/PropertyInt.h"
#pragma once

namespace HARMONY
{
	template<typename C>
	inline PropertyInt32::PropertyInt32(const TCHAR* name, int32_t C::* memberptr)
	:PropertyInt32::BasicProperty(name,memberptr)
	{
		
	}

	template<typename C>
	inline PropertyInt64::PropertyInt64(const TCHAR* name, int64_t C::* memberptr)
	:PropertyInt64::BasicProperty(name, memberptr)
	{

	}
}