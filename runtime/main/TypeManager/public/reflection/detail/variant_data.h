#pragma once
#include<string>

namespace HARMONY
{
	class type;
	namespace DETAIL
	{
		struct variant_data
		{
			variant_data(type vartype)
			:_type(vartype){};
			type _type;
			void* _typeAdder;
			void* _wrappedAdder;
		};
	}
}