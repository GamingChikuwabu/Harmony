#pragma once
#include"Property/BasicProperty.h"

namespace HARMONY
{
	class REFLECTION_API PropertyFloat : public BasicProperty<float>
	{
	public:
		template<typename C>
		PropertyFloat(const TCHAR* name, float C::* memberptr);
		inline PropertyKind GetKind()override;	
	};

	class REFLECTION_API PropertyDouble : public BasicProperty<double>
	{
	public:
		template<typename C>
		PropertyDouble(const TCHAR* name, float C::* memberptr);
		inline PropertyKind GetKind()override;
	};
}

#include"detail/PropertyFloat_impl.inl"