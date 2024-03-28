#pragma once
#include<functional>
#include<any>
#include"HMArray.h"

namespace HARMONY
{
	class Construction
	{
	public:
		void* invoke()const;
		template<typename ...Args>
		void* invoke(Args... arg)const;
		template<class C, typename ...Args>
		void add()const;
	private:
		HMArray<std::any> _constructor;
	};
}

#include"deteil/Construction_impl.inl"