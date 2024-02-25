#pragma once
#include<type_traits>
#include<string>

namespace HARMONY
{
	namespace DETAIL
	{
		struct variant_data;
		struct data_address_container;
	}
	class type;
	class TYPEMANAGER_API variant
	{
	public:
		template<typename T>
		variant(T&& obj);
		variant(const variant& var);
		~variant();
		inline void operator=(const variant& var);
		inline bool operator==(const variant& var)const;
		inline bool operator!=(const variant& var)const;
		inline bool IsValid()const;
		inline type GetType()const;
		inline type GetWrappedType()const;
		inline type GetRawType()const;
		inline type GetArrayRawType()const;

		template<typename T>
		T Convert()const;
		template<typename T>
		bool Convert(T& object)const;

		int8_t		ToInt8()const;
		int16_t		ToInt16()const;
		int32_t		ToInt32()const;
		int64_t		ToInt64()const;
		uint8_t		ToUint8()const;
		uint16_t	ToUint16()const;
		uint32_t	ToUint32()const;
		uint64_t	ToUint64()const;
		std::string ToString()const;

	private:
		variant();
		friend class instance;
		template<typename T>
		std::enable_if_t<std::is_arithmetic_v<T>, T> Convert_imple()const;

		template<typename T>
		std::enable_if_t<!std::is_arithmetic_v<T>, T> Convert_imple()const;

		DETAIL::data_address_container GetDataAddressContainer()const;
	private:
		DETAIL::variant_data* _data;
	};
}

#include"reflection/impl/variant_impl.h"