#include"Class.h"
#pragma once

namespace HARMONY
{
	template<class C>
	inline Class::Class(const TCHAR* name)
	:_name(name)
	,_size(sizeof(C))
	{
		Construction c = []()->void* {
			void* ptr =  (void*)GC_malloc(_size);
			new (ptr) C();
		};
	}

	template<typename ...Args>
	void* Class::Create(Args... arg)
	{

	}
}