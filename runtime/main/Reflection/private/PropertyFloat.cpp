#include"Property/PropertyFloat.h"

namespace HARMONY
{
	inline PropertyKind PropertyFloat::GetKind()
	{
		return PropertyKind::Float;
	}

	inline PropertyKind PropertyDouble::GetKind()
	{
		return PropertyKind::Double;
	}
}