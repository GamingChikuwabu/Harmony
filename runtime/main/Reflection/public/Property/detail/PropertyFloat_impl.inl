#include "Property/PropertyFloat.h"
#pragma once
#include"Property/PropertyAccessor.h"

namespace HARMONY
{
	template<typename C>
	inline PropertyFloat::PropertyFloat(const TCHAR* name, float C::* memberptr)
	:PropertyFloat::Property(name,new PropertyAccessor<C,float>(memberptr))
	{
		
	}

	template<typename C>
	inline float HARMONY::PropertyFloat::GetValue(C* instance)
	{
		PropertyAccessor<C, float>* propaccess = GetAccessorPtr<PropertyAccessor<C, float>*>();
		return propaccess->GetValue(instance);
	}

	template<typename C>
	inline bool PropertyFloat::SetValue(C* instance, float value)
	{
		PropertyAccessor<C, float>* propaccess = GetAccessorPtr<PropertyAccessor<C, float>*>();
		return propaccess->SetValue(instance,value);
	}


}