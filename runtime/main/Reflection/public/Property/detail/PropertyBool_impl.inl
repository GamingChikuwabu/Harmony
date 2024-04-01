#include "Property/PropertyBool.h"
#pragma once
#include"Property/PropertyAccessor.h"

namespace HARMONY
{
	template<typename C>
	inline PropertyBool::PropertyBool(const TCHAR* name, bool C::* memberptr)
	:PropertyBool::BasicProperty(name, memberptr)
	{

	}
}