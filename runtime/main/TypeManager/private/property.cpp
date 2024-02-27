#include"property.h"
#include"property_wrapper_base.h"
#include"type.h"


namespace HARMONY
{
	namespace DETAIL
	{
		template<>
		property DETAIL::create_item(const property_wrapper_base* wrapper)
		{
			return HARMONY::property(wrapper);
		}

		template<>
		property create_invalid_item()
		{
			static const property_wrapper_base invalid_wrapper("", GetInvalidType());
			return property(&invalid_wrapper);
		}
	}
	
	bool property::IsVaild()
	{
		return _data->IsVaild();
	}
	access_level property::get_access_level()
	{
		return _data->GetAccessLevel();
	}
	bool property::IsReadOnry() const noexcept
	{
		return _data->IsReadOnry();
	}
	bool property::IsStatic() const noexcept
	{
		return _data->IsStatic();
	}
	const std::string& property::GetName() const
	{
		return _data->GetName();
	}
	type property::GetType() const noexcept
	{
		return _data->GetType();
	}
	type property::GetDeclaringType() const noexcept
	{
		return _data->GetDeclaringType();
	}
	variant property::GetValue(variant obj)
	{
		return _data->GetValue(obj);
	}
	variant property::SetValue(variant obj, variant value)
	{
		return _data->SetValue(obj,value);
	}
	property::property(const DETAIL::property_wrapper_base* wrapper)
	:_data(wrapper)
	{
		
	}
}