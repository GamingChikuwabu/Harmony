#include"Property/PropertyString.h"
#pragma once

namespace HARMONY
{
	template<typename C>
	inline PropertyString::PropertyString(const TCHAR* name, HMString C::* memberptr)
	:PropertyString::BasicProperty(name, memberptr)
	{
	}
}