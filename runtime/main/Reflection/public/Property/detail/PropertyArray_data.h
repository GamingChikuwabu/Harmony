#pragma once
#include"Array/HMArray.h"

namespace HARMONY
{
	template<typename C,typename T>
	class PropertyArrayData
	{
	public:
		using accessor = HMArray<T> C::*;
		PropertyArrayData(accessor acc):_acc(acc);
		using Type = T;
		template<typename C>
		inline void* GetValue(C* instance)
		{
			return instance->*_acc;
		}

		template<typename C>
		bool SetValue(C* instance,HMArray<T>* obj)
		{
			instance->*_acc = obj;
		}
	private:
		accessor _acc;
	};
}