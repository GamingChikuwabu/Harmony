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
	bool variant::isValid() const
	{
		return false;
	}
	type variant::GetType() const
	{
		return _data->_type;
	}
}