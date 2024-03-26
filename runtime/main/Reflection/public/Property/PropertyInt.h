#pragma once
#include"Property.h"

namespace HARMONY
{
	class REFLECTION_API PropertyInt : public Property
	{
	public:
		template<typename C>
		PropertyInt(const TCHAR* name,int C::* memberptr);
		template<typename C>
		int GetValue(C* instane);
		template<typename C>
		bool SetValue(C* instance, int value);
		inline PropertyKind GetKind()override;
	};
}

#include"detail/PropertyInt_impl.inl"