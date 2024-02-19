#include"type.h"
#include"type_data.h"

namespace HARMONY
{
	type::type(const type& other)
	{
		_data = new DETAIL::type_data();
	}
	void type::operator=(const type& other)
	{

	}
	type::type()
	{

	}
	type::type(DETAIL::type_data* data) :_data(data)
	{

	}
}