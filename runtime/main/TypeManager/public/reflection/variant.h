#pragma once
#include<cinttypes>
#include<string>
#include<memory>

namespace HARMONY
{
	namespace DETAIL
	{
		struct data_address_container;
	}

	class type;
	class TYPEMANAGER_API variant
	{
	public:
		variant();

		template<typename T>
		variant(T& obj);

		template<typename T>
		T GetValue();

		template<typename T>
		T Convert()const;

		template<typename T>
		bool Convert(T& refObj)const;

		template<typename T>
		bool CanConvert() const;

		bool CanConvert(const type& type)const;

		type GetType()const noexcept;

		type GetWrappedType()const noexcept;

		bool isAssociativeContainer() const;

		bool isSequentialContainer() const;

		bool ToBool()const;

		int8_t ToInt8()const;

		int16_t ToInt16()const;

		int32_t ToInt32()const;

		int64_t ToInt64()const;

		uint8_t  ToUint8()const;

		uint16_t ToUint16()const;

		uint32_t ToUint32()const;

		uint64_t ToUint64()const;

		float ToFloat()const;

		double ToDouble()const;

		std::string ToString()const;
	private:
		std::unique_ptr<DETAIL::data_address_container> _data;
	};
}

#include"reflection/impl/variant_impl.h"