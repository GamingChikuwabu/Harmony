#pragma once
#include"Property/BasicProperty.h"

namespace HARMONY
{
	class REFLECTION_API PropertyBool : public BasicProperty<bool>
	{
	public:
		template<typename C>
		PropertyBool(const TCHAR* name, bool C::* memberptr);
		inline PropertyKind GetKind()override;
	};
}

#include"detail/PropertyBool_impl.inl"