#pragma once

namespace HARMONY
{
	class type;
	namespace DETAIL
	{
		struct data_address_container
		{
			type _type;
			type _wrappedType;
			void* _typeAddress;
			void* _wrappedTypeAddress;
		};
	}
}