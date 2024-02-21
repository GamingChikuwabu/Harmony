#include"registration.h"
#include"type_data.h"

namespace HARMONY
{
	DETAIL::type_data* registration::AddItem(std::unique_ptr<DETAIL::type_data> _data)
	{
		_typeData.push_back(std::move(_data));
		return _typeData.back().get();
	}
}