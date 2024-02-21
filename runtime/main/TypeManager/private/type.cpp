#include"type.h"
#include"type_data.h"

namespace HARMONY
{
	type::type(const type& other)
	:_data(other._data)
	{

	}
	void type::operator=(const type& other)
	{
		_data = other._data;
	}
	bool type::operator==(const type& other)
	{
		if (_data->_name == other._data->_name)
		{
			return true;
		}
		return false;
	}
	bool type::operator!=(const type& other)
	{
		return !(*this == other);
	}
	std::string type::GetName()
	{
		return _data->_name;
	}

	size_t type::GetSizeOf() const noexcept
	{
		return _data->_size;
	}

	type type::GetWrappedType() const
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_wrappermapper))) {
			return type(_data->_wrappedType);
		}
		return type(_data);
	}

	type type::GetRawType() const
	{
		return CreateType(_data->_rawType);
	}

	type type::GetArrayRawType() const
	{
		return CreateType(_data->_arrayRawType);
	}

	bool type::IsValid() const
	{
		return _data->_isValid;
	}
	bool type::IsArithmetic()const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_arithmetic)))
		{
			return true;
		}
		return false;
	}
	bool type::IsPointer()const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_pointer)))
		{
			return true;
		}
		return false;
	}
	bool type::IsArray()const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_array)))
		{
			return true;
		}
		return false;
	}
	bool type::IsClass()const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_class)))
		{
			return true;
		}
		return false;
	}
	bool type::IsEnum() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_enum)))
		{
			return true;
		}
		return false;
	}
	bool type::IsFunctionPointer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_function_pointer)))
		{
			return true;
		}
		return false;
	}
	bool type::IsMemberObjectPointer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_member_object_pointer)))
		{
			return true;
		}
		return false;
	}
	bool type::IsMemberFunctionPointer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_member_function_pointer))) 
		{
			return true;
		}
		return false;
	}
	bool type::IsWrapped() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_wrappermapper)))
		{
			return true;
		}
		return false;
	}

	bool type::IsSequentialContainer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_sequential_container)))
		{
			return true;
		}
		return false;
	}

	bool type::IsAssociativeContainer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_associative_container)))
		{
			return true;
		}
		return false;
	}
	type::type()
	:_data(GetInvalidTypeData())
	{

	}
	type::type(DETAIL::type_data* data) :_data(data)
	{

	}
	type GetInvalidType()
	{
		DETAIL::type_data* temp = DETAIL::GetInvalidTypeData();
		return type(temp);
	}
}