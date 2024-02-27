#pragma once
#include"access_level.h"
#include<string>
#include"detail/misc/class_item_mapper.h"

namespace HARMONY
{
	class type;
	class variant;
	namespace DETAIL
	{
		class property_wrapper_base;
	}
	class TYPEMANAGER_API property
	{
	public:
		bool IsVaild();
		explicit operator bool() const noexcept;
		access_level get_access_level();
		bool IsReadOnry() const noexcept;
		bool IsStatic() const noexcept;
		const std::string& GetName()const;
		type GetType()const noexcept;
		type GetDeclaringType()const noexcept;
		variant GetValue(variant obj);
		variant SetValue(variant obj,variant value);
	private:
		property(const DETAIL::property_wrapper_base* wrapper);
		template<typename T>
		friend T DETAIL::create_item(const DETAIL::class_item_to_wrapper_t<T>* wrapper);
		template<typename T>
		friend T DETAIL::create_invalid_item();
		const DETAIL::property_wrapper_base* _data;
	};
}