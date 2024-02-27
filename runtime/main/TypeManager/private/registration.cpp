#include"registration.h"
#include"detail/type/type_data.h"
#include"type.h"

namespace HARMONY
{
	DETAIL::type_data* registration::AddItem(std::unique_ptr<DETAIL::type_data> _data)
	{
		_typeData.push_back(std::move(_data));
		return _typeData.back().get();
	}
	void registration::RegisterCustomTypeName(type regType, std::string _name)
	{
		_customTypeName[_name] = regType;
	}
	type registration::GetCustomTypeName(const char* name)
	{
		return _customTypeName[name];
	}
}