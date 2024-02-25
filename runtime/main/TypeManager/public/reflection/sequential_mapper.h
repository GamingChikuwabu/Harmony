#pragma once

namespace HARMONY
{
	template<typename T>
	struct sequential_container_mapper
	{
		using is_valid = std::false_type;
	}
}

#include"reflection/impl/sequential_mapper_impl.h"