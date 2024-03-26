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

	}

	template<typename T>
	template<typename C>
	inline T BasicProperty<T>::GetValue(C* instance)
	{
		PropertyAccessor<C, T>* propaccess = GetAccessorPtr<PropertyAccessor<C, T>*>();
		return propaccess->GetValue(instance);
	}

	template<typename T>
	template<typename C>
	inline bool BasicProperty<T>::SetValue(C* instance, T value)
	{
		PropertyAccessor<C, T>* propaccess = GetAccessorPtr<PropertyAccessor<C, T>*>();
		return propaccess->SetValue(instance, value);
	}
}