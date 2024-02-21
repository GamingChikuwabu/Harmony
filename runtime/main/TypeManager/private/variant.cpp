#include "variant.h"
#include"type.h"
#include"detail/variant_data.h"

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
}