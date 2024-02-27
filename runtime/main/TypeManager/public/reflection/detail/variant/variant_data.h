#pragma once
#include<string>
#include<type_traits>

namespace HARMONY
{
	class type;
	namespace DETAIL
	{
		struct variant_data
		{
			variant_data(type vartype,void* address):_type(vartype),_typeAdder(address) {};
			type _type;
			void* _typeAdder;
		};
	}
}