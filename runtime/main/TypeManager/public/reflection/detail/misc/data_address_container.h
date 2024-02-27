#pragma once

namespace HARMONY
{
	class type;
	namespace DETAIL
	{
		struct data_address_container
		{
			type    m_type;
			type    m_wrapped_type;
			void* m_data_address;
			void* m_data_address_wrapped_type;
		};
	}
}