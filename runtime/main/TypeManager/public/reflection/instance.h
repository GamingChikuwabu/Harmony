#pragma once
#include"data_address_container.h"

namespace HARMONY
{
	class variant;
	class type;
	class instance
	{
	public:
		inline instance()noexcept;
		inline instance(const variant& var)noexcept;
		inline instance(const instance& var)noexcept;
		template<typename T>
		inline instance(T& data)noexcept;
		template<typename T>
		inline T* TryConvert()const noexcept;
		inline bool IsValid()const noexcept;
		inline type GetType()const noexcept;
		inline instance GetWrappedInstance()const noexcept;
		inline type GetDerivedType()const noexcept;
	private:
		instance& operator=(const instance& other)noexcept;
		DETAIL::data_address_container _data_container;
	};	
}
#include"reflection/impl/instance_impl.h"