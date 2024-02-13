#include"Types/property.h"
#include"property_data.h"

namespace HARMONY
{
	const std::string Property::GetName() const
	{
		return _data->_propertyName;
	}
	void* Property::GetValue(void* class_instance)
	{
		return _data->_getFunc(class_instance);
	}
	void Property::SetValue(void* class_instance, const std::any& value)
	{
		_data->_setFunc(class_instance, value);
	}
	ACCESS_LEVEL Property::GetAccessLevel() const
	{
		return _data->_accessLevel;
	}
}