#include"Property/PropertyClass.h"
#pragma once
namespace HARMONY
{
	template<typename C, typename AC>
	inline PropertyClass::PropertyClass(const TCHAR* name, AC C::* memberptr)
		:PropertyClass::Property(name, memberptr, sizeof(AC))
	{
		getter = [memberptr](void* instance)->void* {
			C* classPtr = reinterpret_cast<C*>(instance);
			return (void*)classPtr->*memberptr;
			};

		setter = [memberptr](void* instance, void* value)->bool {
			C* classPtr = reinterpret_cast<C*>(instance);
			AC* valuePtr = reinterpret_cast<AC*>(value);
			classPtr->*memberptr = *valuePtr;
			return true;
			};
	}

	template<typename C>
	inline void* PropertyClass::GetValue(C* instance)
	{
		return getter(instance);
	}

	template<typename C>
	inline bool PropertyClass::SetValue(C* instance,void* value)
	{
		return setter(instance,value);
	}

	template<typename T, typename C>
	T* PropertyClass::Convert(C* instance)
	{
		return static_cast<T*>(getter(instance));
	}
}