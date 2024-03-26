#pragma once
#include"Property/Property.h"

namespace HARMONY
{
	template<typename T>
	class REFLECTION_API BasicProperty: public Property
	{
	public:
		template<typename C>
		BasicProperty(const TCHAR* name,T C::* memberPtr);
		template<typename C>
		T GetValue(C* instane);
		template<typename C>
		bool SetValue(C* instance, T value);
	};
}

#include"detail/BasicProperty_impl.inl"