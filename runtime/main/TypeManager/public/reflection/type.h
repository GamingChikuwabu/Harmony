#pragma once

namespace HARMONY
{
	namespace DETAIL
	{
		struct type_data;
	}
	class type
	{
	public:
		type(const type& other);
		void operator=(const type& other);
		template<typename T>
		static type Get();
	private:
		type();
		type(DETAIL::type_data* data);
		DETAIL::type_data* _data;
	};
}

#include"reflection/impl/type_impl.h"