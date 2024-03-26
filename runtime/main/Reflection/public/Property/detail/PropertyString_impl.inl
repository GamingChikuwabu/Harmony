#include"Property/PropertyString.h"
#pragma once
#include"Property/PropertyAccessor.h"
#include"HMString.h"

namespace HARMONY
{
	template<typename C>
	inline PropertyString::PropertyString(const TCHAR* name, HMString C::* memberptr)
	:PropertyString::Property(name,new PropertyAccessor<C,HMString>(memberptr))
	{
	}

	template<typename C>
	inline const HMString HARMONY::PropertyString::GetValue(C* instance)
	{
		PropertyAccessor<C, HMString>* propaccess = GetAccessorPtr<PropertyAccessor<C, HMString>*>();
		return propaccess->GetValue(instance);
	}

	template<typename C>
	inline bool PropertyString::SetValue(C* instance, HMString& value)
	{
		PropertyAccessor<C, HMString>* propaccess = GetAccessorPtr<PropertyAccessor<C, HMString>*>();
		return propaccess->SetValue(instance, value);
	}
}