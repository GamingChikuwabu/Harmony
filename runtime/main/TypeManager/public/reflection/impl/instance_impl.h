#include"instance.h"
#pragma once
#include"variant.h"
#include"type.h"
#include"wrapper_mapper.h"


namespace HARMONY
{
	inline instance::instance()noexcept
	:_data_container(DETAIL::data_address_container{ DETAIL::GetInvalidType(), DETAIL::GetInvalidType(),nullptr,nullptr })
	{
	}
	instance::instance(const variant& var)
	:_data_container(var.GetDataAddressContainer())
	{}

	instance::instance(const instance& var)
	:_data_container(var._data_container)
	{}

	bool instance::IsValid() const noexcept
	{
		return false;
	}
	type instance::GetType() const noexcept
	{
		return _data_container.m_type;
	}
	instance instance::GetWrappedInstance() const noexcept
	{
		return _data_container.m_data_address_wrapped_type;
	}
	type instance::GetDerivedType() const noexcept
	{
		return DETAIL::GetInvalidType();
	}
	instance& instance::operator=(const instance& other) noexcept
	{
		// TODO: return ステートメントをここに挿入します
	}
	template<typename T>
	inline instance::instance(T& data) noexcept
		:_data_container(DETAIL::data_address_container{
				type::Get<T>(),
				type::Get<DETAIL::wrapper_mapper_t<T>>(),
				DETAIL::get_void_ptr(std::addressof(data)),DETAIL::get_void_ptr(DETAIL::wrapped_raw_addressof(data))
		})
	{

	}
	template<typename T>
	inline T* instance::TryConvert() const noexcept
	{
		return nullptr;
	}
}