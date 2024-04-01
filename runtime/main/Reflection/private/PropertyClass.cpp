#include"PropertyClass.h"
#include"Refrection.hpp"

namespace HARMONY
{
	Class* PropertyClass::GetClass()
	{
		return classGetter();
	}

	PropertyKind PropertyClass::GetKind()
	{
		return PropertyKind::Class;
	}
}