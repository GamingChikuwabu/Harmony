#include"Property/Property.h"

namespace HARMONY
{
	Property::Property(const TCHAR* name, void* accessor):_name(name),accessor(accessor)
	{
		
	}

	Property::~Property()
	{
		delete accessor;
	}
	
	const TCHAR* Property::GetName()
	{
		return _name;
	}
}