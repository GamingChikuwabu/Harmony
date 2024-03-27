#pragma once
#include<functional>
#include<any>
#include"HMArray.h"

namespace HARMONY
{
	class Construction
	{
	public:
		void* invoke();
		template<typename ...Args>
		void* invoke(Args... arg);
		template<class C, typename ...Args>
		void add();
	private:
		HMArray<std::any> _constructor;
	};
}

#include"deteil/Construction_impl.inl"