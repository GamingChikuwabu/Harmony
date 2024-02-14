#include"Types/ItemCreator.h"
#include"type_data.h"
#include"property_data.h"

namespace HARMONY
{
	namespace DETAIL
	{
		Type ItemCreator::CreateType(std::string name, std::size_t size, std::type_index index, TYPE_CATEGORY cate)
		{
			Type type;
			type._data = std::make_shared<Type_Data>(cate,name,size,index);
			return type;
		}

		Property ItemCreator::CreateProperty(std::string name, std::function<void(void*, std::any)> setter, std::function<void* (void*)> getter, ACCESS_LEVEL acc)
		{
			auto data = std::make_shared<Property_Data>();
			Property prop{ data };
			prop._data->_accessLevel = acc;
			prop._data->_setFunc = setter;
			prop._data->_getFunc = getter;
			prop._data->_propertyName = name;
			return prop;
		}
	}
}