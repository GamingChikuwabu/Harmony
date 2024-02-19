#include"enumeration.h"
#include"type_data.h"
#include"type.h"

namespace HARMONY
{
	enumeration::enumeration(const enumeration& value)
		:_data(value._data.get())
	{

	}
	enumeration::enumeration(const enumeration&& value)
		:_data(value._data.get())
	{
	}
	type enumeration::GetType() const noexcept
	{
		return _data->_type;
	}
	std::size_t enumeration::GetCount() const noexcept
	{
		return _data->_size;
	}
	std::size_t enumeration::NameToValue(std::string name) const noexcept
	{
		for (const auto& pair : _data->_valueNamePair) {
			if (pair.second == name) {
				return pair.first; // 名前が一致した場合、対応する列挙型の値を返す
			}
		}
		return 0;
	}
	std::string enumeration::ValueToString(std::size_t value) const noexcept
	{
		return _data->_valueNamePair[value];
	}
	std::string enumeration::GetName() const noexcept
	{
		return _data->_typename;
	}
	enumeration::enumeration()
	{

	}
	enumeration::enumeration(DETAIL::enumeration_data* data)
	:_data(data)
	{

	}
}