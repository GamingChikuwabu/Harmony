#pragma once


namespace HARMONY
{
	namespace DETAIL
	{
		struct variant_data;
	}
	class type;
	class TYPEMANAGER_API variant
	{
	public:
		template<typename T>
		variant(T&& obj);
		template<typename T>
		variant(T& obj);
		variant(const variant& var);
		~variant();
		inline void operator=(const variant& var);
		inline bool operator==(const variant& var)const;
		inline bool operator!=(const variant& var)const;
		inline bool IsValid()const;
		inline type GetType()const;
		inline type GetWrappedType()const;
		inline variant GetWrappedValue()const;
		template<typename T>
		T Convert();

	private:
		variant();
		DETAIL::variant_data* _data;
	};
}

#include"reflection/impl/variant_impl.h"