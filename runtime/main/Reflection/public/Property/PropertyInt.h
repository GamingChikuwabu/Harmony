#pragma once
#include"BasicProperty.h"
#include<cinttypes>

namespace HARMONY
{
	class REFLECTION_API PropertyInt32 : public Property
	{
	public:
		PropertyInt32(const TCHAR* name);
		inline PropertyKind GetKind()override;
		virtual int32_t GetValue(void* holderClass = nullptr);
		virtual bool SetValue(int32_t value, void* holderClass = nullptr);
	};

	class REFLECTION_API PropertyInt64 : public Property
	{
	public:
		PropertyInt64(const TCHAR* name);
		inline PropertyKind GetKind()override;
		virtual int64_t GetValue(void* holderClass = nullptr);
		virtual bool SetValue(int64_t value, void* holderClass = nullptr);
	};
}

#include"detail/PropertyInt_impl.inl"