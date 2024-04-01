#include"Class.h"
#pragma once
#include"Class/deteil/ClassData.h"
#include"Construction/Construction.h"

namespace HARMONY
{
	template<typename ...Args>
	void* Class::Create(Args... arg)
	{
		return _data->_construction->invoke(arg);
	}
}