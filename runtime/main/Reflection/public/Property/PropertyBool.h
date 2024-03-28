#pragma once
#include"Property/BasicProperty.h"

namespace HARMONY
{
	class PropertyBool : public BasicProperty<bool>
	{
	public:
		template<typename C>
		PropertyBool(const TCHAR* name, float C::* memberptr);
		inline PropertyKind GetKind()override;
	};
}

#include"detail/PropertyBool_impl.inl"