#pragma once
#include"void_ptr_trats.h"
#include<vector>

template<typename T, typename Archive>
void Serialize(const std::vector<T>& vec,Archive ar)
{
	for (auto v : vec)
	{
		ar& vec;
	}
}

namespace HARMONY
{
	template<typename T, typename Tp = std::remove_cv_t<std::remove_reference_t<T>>>
	variant::variant(T&& var)
	{
		_ptr = get_void_ptr(var);
	};
}