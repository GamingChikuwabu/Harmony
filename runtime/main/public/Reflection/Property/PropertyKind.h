#pragma once
#include<type_traits>
#include"PropertyAccessor.h"
#include"Property.h"

namespace HARMONY
{
	enum class PropertyKind
	{
		Bool,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Float,
		Double,
		String,
		Array,
		Map,
		UMap,
		Class,
		Object,
		MAX
	};
}