#include"Property/PropertyInt.h"
#pragma once
#include"Property/PropertyAccessor.h"

namespace HARMONY
{
	template<typename C>
	inline PropertyInt::PropertyInt(const TCHAR* name, int C::* memberptr)
	:PropertyInt::Property(name, new PropertyAccessor<C, int>(memberptr))
	{
		
	}

	template<typename C>
	inline int PropertyInt::GetValue(C* instance)
	{
		PropertyAccessor<C, int>* propaccess = GetAccessorPtr<PropertyAccessor<C, int>*>();
		return propaccess->GetValue(instance);
	}

	template<typename C>
	inline bool PropertyInt::SetValue(C* instance, int value)
	{
		PropertyAccessor<C, int>* propaccess = GetAccessorPtr<PropertyAccessor<C, int>*>();
		return propaccess->SetValue(instance,value);
	}
}