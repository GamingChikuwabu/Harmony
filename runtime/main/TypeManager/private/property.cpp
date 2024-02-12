#include"Types/property.h"

namespace HARMONY
{
	const std::string Property::GetName() const
	{
		return std::string();
	}
	void Property::SetValue(void* class_instance, std::any value)
	{
	}
	std::any Property::GetValue(void* class_instance)
	{
		return std::any();
	}
	PROPERTY_ACCESS_LEVEL Property::GetAccessLevel() const
	{
		return PROPERTY_ACCESS_LEVEL();
	}
}