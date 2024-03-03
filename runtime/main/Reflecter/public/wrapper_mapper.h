#pragma once

namespace HARMONY
{
	namespace DETEIL { struct invalid_wrapper_type { }; }
	template<typename T>
	struct wrapper_mapper
	{
		using wrapped_type = DETEIL::invalid_wrapper_type;
		using type = T;
	};
}

#include"inl/wrapper_mapper.inl"