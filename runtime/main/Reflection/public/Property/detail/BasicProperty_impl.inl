#include"Property/BasicProperty.h"
#pragma once
#include"Property/PropertyAccessor.h"
#include"gc/gc.h"
#include<new>

namespace HARMONY
{
	template<typename T>
	template<typename C>
	inline BasicProperty<T>::BasicProperty(const TCHAR* name, T C::* memberPtr)
	:BasicProperty<T>::Property
	(
		name,
		new ((void*)GC_malloc(sizeof(PropertyAccessor<C, T>))) PropertyAccessor<C, T>(memberPtr),
		sizeof(T)
	)
	{
		getter = [memberPtr](void* instance)->T {
			C* classPtr = reinterpret_cast<C*>(instance);
			return classPtr->*memberPtr;
		};

		setter = [memberPtr](void* instance, T value)->bool {
			C* classPtr = reinterpret_cast<C*>(instance);
			classPtr->*memberPtr = value;
			return true;
		};
	}

	template<typename T>
	T BasicProperty<T>::GetValue(void* instane)
	{
		return getter(instane);
	}
}