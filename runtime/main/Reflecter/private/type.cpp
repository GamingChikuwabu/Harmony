#include"type.h"

namespace HARMONY
{
	type::type()
	{

	}

	type::type(const type& other)
	{

	}

	const char* type::GetName() const
	{
		return nullptr;
	}

	size_t type::GetSize() const
	{
		return size_t();
	}

	type type::GetRawType()const
	{
		return type();
	}

	type type::GetWrappedType()const
	{
		return type();
	}
}