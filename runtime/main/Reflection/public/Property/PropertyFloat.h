#pragma once
#include"Property.h"

namespace HARMONY
{
	class PropertyFloat : public Property
	{
	public:
		template<typename C>
		PropertyFloat(const TCHAR* name, float C::* memberptr);
		template<typename C>
		float GetValue(C* instane);
		template<typename C>
		bool SetValue(C* instance, float value);
		inline PropertyKind GetKind()override;	
	};
}

#include"detail/PropertyFloat_impl.inl"