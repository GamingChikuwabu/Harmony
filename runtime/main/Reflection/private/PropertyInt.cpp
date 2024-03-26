#include"Property/PropertyInt.h"
namespace HARMONY
{
	inline PropertyKind PropertyInt32::GetKind()
	{
		return PropertyKind::Int32;
	}
	inline PropertyKind PropertyInt64::GetKind()
	{
		return PropertyKind::Int64;
	}
}