#include"Property/Property.h"

namespace HARMONY
{
	Property::Property(const TCHAR* name, void* accessor, size_t size):_name(name),accessor(accessor),_size(size)
	{
		
	}
	
	const TCHAR* Property::GetName()
	{
		return _name;
	}
}