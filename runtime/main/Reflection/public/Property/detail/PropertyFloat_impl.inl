#include "Property/PropertyFloat.h"
#pragma once
#include"Property/PropertyAccessor.h"

namespace HARMONY
{
	template<typename C>
	inline PropertyFloat::PropertyFloat(const TCHAR* name, float C::* memberptr)
	:PropertyFloat::BasicProperty(name, memberptr)
	{
		
	}

}