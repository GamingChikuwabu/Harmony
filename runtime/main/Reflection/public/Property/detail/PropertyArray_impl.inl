#include"Property/PropertyArray.h"
#pragma once
#include"Property/PropertyAccessor.h"
#include"PropertyArray_data.h"
#include"gc/gc.h"
#include<new>

namespace HARMONY
{
	template<typename C, typename T>
	inline PropertyArray::PropertyArray(const TCHAR* name, HARMONY::HMArray<T> C::* memberptr)
	:PropertyArray::Property
	(
		name,
		new ((void*)GC_malloc(sizeof(PropertyArrayData<C, T>))) PropertyArrayData<C, T>(memberptr)
	)
	{
		
	}

	template<typename C>
	inline void* PropertyArray::GetValue(C * instance)
	{
		PropertyArrayData<C, T>* propaccess = GetAccessorPtr<PropertyArrayData<C, T>*>();
		return propaccess->GetValue(instance);
	}

	template<typename C>
	inline bool PropertyArray::SetValue(C* instance, void* value)
	{
		return false;
	}
}