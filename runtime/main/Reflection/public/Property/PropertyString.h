#pragma once
#include"Property.h"

namespace HARMONY
{
	class REFLECTION_API PropertyString : public Property
	{
	public:
		template<typename C>
		PropertyString(const TCHAR* name, HMString C::* memberptr);
		template<typename C>
		const HMString GetValue(C* instane);
		template<typename C>
		bool SetValue(C* instance, HMString& value);
		inline PropertyKind GetKind()override;
	};
}

#include"detail/PropertyString_impl.inl"