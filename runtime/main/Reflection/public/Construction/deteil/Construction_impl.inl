#include"Construction.h"
#pragma once

namespace HARMONY
{
	template<typename ...Args>
	inline void* Construction::invoke(Args ...arg) const
	{
		for (auto fn : _constructor)
		{
			auto temp = std::any_cast<std::function<void* (Args...)>>(fn);
			if (temp)
			{
				return temp(arg);
			}
		}
		return nullptr;
	}

	template<class C, typename ...Args>
	inline void Construction::add()const
	{
		std::function<void* (Args...)> cons = [](Args... arg)->void*			
		{
			void* ptr = (void*)GC_malloc(sizeof(C));
			new (ptr) C(arg);
			return ptr;
		};
		_constructor.Add(std::move(cons));
	}

}