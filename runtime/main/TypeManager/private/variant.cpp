#include "variant.h"
#include"type.h"
#include"detail/variant/variant_data.h"
#include"detail/misc/data_address_container.h"

namespace HARMONY
{
	using namespace DETAIL;
	variant::variant()
	{
		
	}
	variant::variant(const variant& var)
	{

	}
	variant::~variant()
	{

	}
	void variant::operator=(const variant& var)
	{
		_data = var._data;
	}
	inline bool variant::operator==(const variant& var) const
	{
		return false;
	}
	inline bool variant::operator!=(const variant& var) const
	{
		return false;
	}
	bool variant::IsValid() const
	{
		return false;
	}
	type variant::GetType() const
	{
		return _data->_type;
	}
	inline type variant::GetWrappedType() const
	{
		return _data->_type.GetWrappedType();
	}
	inline type variant::GetRawType() const
	{
		return _data->_type.GetRawType();
	}
	inline type variant::GetArrayRawType() const
	{
		return _data->_type.GetArrayRawType();
	}
	int8_t variant::ToInt8()const
	{
		return Convert<int8_t>();
	}
	int16_t variant::ToInt16()const
	{
		return Convert<int8_t>();
	}
	int32_t variant::ToInt32()const
	{
		return Convert<int8_t>();
	}
	int64_t variant::ToInt64()const
	{
		return Convert<int8_t>();
	}
	uint8_t variant::ToUint8()const
	{
		return Convert<int8_t>();
	}
	uint16_t variant::ToUint16()const
	{
		return Convert<int8_t>();
	}
	uint32_t variant::ToUint32()const
	{
		return Convert<int8_t>();
	}
	uint64_t variant::ToUint64()const
	{
		return Convert<int8_t>();
	}
	std::string variant::ToString() const
	{
		return Convert<std::string>();
	}
}