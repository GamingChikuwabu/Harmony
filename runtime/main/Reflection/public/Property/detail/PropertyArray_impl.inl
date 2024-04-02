#include"Property/PropertyArray.h"
#pragma once
#include"Property/PropertyAccessor.h"
#include"gc/gc.h"
#include<new>

namespace HARMONY
{

	template<typename C, typename T>
	inline PropertyArray::PropertyArray(const TCHAR* name, HARMONY::HMArray<T> C::* memberptr)
	:PropertyArray::Property
	(
		name,
		nullptr,
		sizeof(HARMONY::HMArray<T>)
	),
	_innerSize(sizeof(T)),
	_innerKind(innerkind<T>::value),
	_innerIsPointer(std::is_pointer_v<T>)
	{
		Class* _temp = nullptr;
		if constexpr (std::is_pointer_v<T>)
		{
			if ()
			_temp = ;
		}
		else if constexpr (HasGetClassMethod<std::remove_pointer_t<T>>)
		{
			_temp = T::StaticGetClass();
		}

		GetScriptArrayFunc = [memberptr](void* classinstance)->ScriptArray {
			C* pclass = reinterpret_cast<C*>(classinstance);
			return ScriptArray(&(pclass->*memberptr), );
		};
	}
}