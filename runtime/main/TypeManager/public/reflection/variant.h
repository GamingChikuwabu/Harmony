#pragma once


namespace HARMONY
{
	namespace DETAIL
	{
		struct variant_data;
	}
	class type;
	class variant
	{
	public:
		template<typename T>
		variant(T& obj);
		variant(const variant& var);
		~variant();
		void operator=(const variant& var);
		bool isValid()const;
		type GetType()const;
	private:
		variant();
		DETAIL::variant_data* _data;
	};
}

#include"reflection/impl/variant_impl.h"