#pragma once
#include"BasicProperty.h"
#include<cinttypes>

namespace HARMONY
{
	class REFLECTION_API PropertyInt32 : public BasicProperty<int32_t>
	{
	public:
		template<typename C>
		PropertyInt32(const TCHAR* name,int32_t C::* memberptr);
		inline PropertyKind GetKind()override;
	};

	class REFLECTION_API PropertyInt64 : public BasicProperty<int64_t>
	{
	public:
		template<typename C>
		PropertyInt64(const TCHAR* name, int64_t C::* memberptr);
		inline PropertyKind GetKind()override;
	};
}

#include"detail/PropertyInt_impl.inl"