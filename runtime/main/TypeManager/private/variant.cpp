#include "Types/variant.h"
#include"Types/type.h"
#include<any>

namespace HARMONY
{
	struct variant_data
	{
		Type _type;
		std::any _value;
	};

	variant& variant::operator=(variant arg)
	{
		// TODO: return ステートメントをここに挿入します
	}

	bool variant::operator==(const variant& arg) const
	{
		return false;
	}

	Type variant::GetType() const
	{
		return _data->_type;
	}

	bool variant::to_bool() const
	{
		return convert<bool>();
	}

	int8_t variant::to_int8() const
	{
		return convert<int8_t>();
	}

	int16_t variant::to_int16() const
	{
		return convert<int16_t>();
	}

	int32_t variant::to_int32() const
	{
		return convert<int32_t>();
	}

	int64_t variant::to_int64() const
	{
		return convert<int64_t>();
	}

	uint8_t variant::to_uint8() const
	{
		return convert<uint8_t>();
	}

	uint16_t variant::to_uint16() const
	{
		return convert<uint16_t>();
	}

	uint32_t variant::to_uint32() const
	{
		return convert<uint32_t>();
	}

	uint64_t variant::to_uint64() const
	{
		return convert<uint64_t>();
	}

	float variant::to_float() const
	{
		return convert<float>();
	}

	double variant::to_double() const
	{
		return convert<double>();
	}

	std::string variant::to_string() const
	{
		return convert<std::string>();
	}
}