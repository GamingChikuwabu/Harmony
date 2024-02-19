#include"variant.h"
#pragma once
#include"type.h"

namespace HARMONY
{
	template<typename T>
	inline variant::variant(T& obj)
	{
		_data = new variant_data(type::Get<T>());

	}
}