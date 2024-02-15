#include"variant.h"
#include"type.h"

namespace HARMONY
{
	variant::variant()
		:_data()
	{

	}
	bool variant::CanConvert(const type& type) const
	{
		return false;
	}
	type variant::GetType() const noexcept
	{
		return type();
	}
	type variant::GetWrappedType() const noexcept
	{
		return _data.type;
	}
	bool variant::isAssociativeContainer() const
	{
		return false;
	}
	bool variant::isSequentialContainer() const
	{
		return false;
	}
	bool variant::ToBool() const
	{
		return Convert<bool>();
	}
	int8_t variant::ToInt8() const
	{
		return Convert<int8_t>();
	}
	int16_t variant::ToInt16() const
	{
		return Convert<int16_t>();
	}
	int32_t variant::ToInt32() const
	{
		return Convert<int32_t>();
	}
	int64_t variant::ToInt64() const
	{
		return Convert<int64_t>();
	}
	uint8_t variant::ToUint8() const
	{
		return Convert<uint8_t>();
	}
	uint16_t variant::ToUint16() const
	{
		return Convert<uint16_t>();
	}
	uint32_t variant::ToUint32() const
	{
		return Convert<uint32_t>();
	}
	uint64_t variant::ToUint64() const
	{
		return Convert<uint64_t>();
	}
	float variant::ToFloat() const
	{
		return Convert<float>();
	}
	double variant::ToDouble() const
	{
		return Convert<double>();
	}
	std::string variant::ToString() const
	{
		return Convert<std::string>(); 
	}
}
