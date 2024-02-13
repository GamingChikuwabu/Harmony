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
		void* memberptr = reinterpret_cast<char*>(class_instance) + _data->_offset;
		return memberptr;
	}
	void Property::SetValue(void* classinstance, const std::any& value)
	{
		_data->_castFunc(classinstance, value); 
	}
	PROPERTY_ACCESS_LEVEL Property::GetAccessLevel() const
	{
		return _data->_accessLevel;
	}
}