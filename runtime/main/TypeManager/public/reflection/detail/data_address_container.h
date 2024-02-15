#pragma once

namespace HARMONY
{
	class Type;
	namespace DETAIL
	{
		struct data_address_container
		{
			Type _type;
			Type _wrappedType;
			void* _typeAdderss;
			void* _wrappedTypeAddress;
		};
	}
}