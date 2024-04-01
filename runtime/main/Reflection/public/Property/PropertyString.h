#pragma once
#include"HMString.h"
#include"BasicProperty.h"

namespace HARMONY
{
	class REFLECTION_API PropertyString : public BasicProperty<HMString>
	{
	public:
		template<typename C>
		PropertyString(const TCHAR* name, HMString C::* memberptr);
		inline PropertyKind GetKind()override;
	};
}

#include"detail/PropertyString_impl.inl"