#include"Property/PropertyInt.h"
#include"HMString.h"

namespace HARMONY
{
	PropertyInt32::PropertyInt32(const TCHAR* name)
	:PropertyInt32::Property(name,sizeof(int32_t))
	{

	}

	inline PropertyKind PropertyInt32::GetKind()
	{
		return PropertyKind::Int32;
	}

	int32_t PropertyInt32::GetValue(void* holderClass = nullptr)
	{
		return 0;
	}

	bool PropertyInt32::SetValue(int32_t value, void* holderClass = nullptr)
	{
		return false;
	}

	PropertyInt64::PropertyInt64(const TCHAR* name)
	:PropertyInt32::Property(name, sizeof(int64_t))
	{

	}

	inline PropertyKind PropertyInt64::GetKind()
	{
		return PropertyKind::Int64;
	}

	int64_t PropertyInt64::GetValue(void* holderClass = nullptr)
	{
		return 0;
	}

	bool PropertyInt64::SetValue(int64_t value, void* holderClass = nullptr)
	{
		return false;
	}
}