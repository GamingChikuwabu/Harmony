#pragma once
#include"Property/BasicProperty.h"

namespace HARMONY
{
	class PropertyFloat : public BasicProperty<float>
	{
	public:
		template<typename C>
		PropertyFloat(const TCHAR* name, float C::* memberptr);
		inline PropertyKind GetKind()override;	
	};
}

#include"detail/PropertyFloat_impl.inl"