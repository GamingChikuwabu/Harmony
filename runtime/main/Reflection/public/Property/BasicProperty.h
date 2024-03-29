#pragma once
#include"Property/Property.h"
#include<functional>

namespace HARMONY
{
	template<typename T>
	class BasicProperty: public Property
	{
	public:
		template<typename C>
		BasicProperty(const TCHAR* name,T C::* memberPtr);
		T GetValue(void* instane);
		bool SetValue(void* instance, T value);
	private:
		std::function<T (void*)> getter;
		std::function<bool(void*, T)> setter;
	};
}

#include"detail/BasicProperty_impl.inl"