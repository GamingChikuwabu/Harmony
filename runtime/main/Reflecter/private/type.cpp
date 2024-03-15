#include"Type.h"
#include<vector>


namespace HARMONY
{
	Type::Type(const Type& other)
	:_data(other._data)
	{

	}
	void Type::operator=(const Type& other)
	{
		_data = other._data;
	}
	bool Type::operator==(const Type& other)
	{
		if (_data->_name == other._data->_name)
		{
			return true;
		}
		return false;
	}
	bool Type::operator!=(const Type& other)
	{
		return !(*this == other);
	}
	std::string Type::GetName()
	{
		return _data->_name;
	}

	size_t Type::GetSizeOf() const noexcept
	{
		return _data->_size;
	}

	Type Type::GetWrappedType() const
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_wrappermapper))) {
			return type(_data->_wrappedType);
		}
		return type(_data);
	}

	Type Type::GetRawType() const
	{
		return CreateType(_data->_rawType);
	}

	Type Type::GetArrayRawType() const
	{
		return CreateType(_data->_arrayRawType);
	}

	Type Type::GetTypeByName(const char* name)
	{
		return registration::GetCustomTypeName(name);
	}

	bool Type::IsValid() const
	{
		return _data->_isValid;
	}
	bool Type::IsArithmetic()const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_arithmetic)))
		{
			return true;
		}
		return false;
	}
	bool Type::IsPointer()const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_pointer)))
		{
			return true;
		}
		return false;
	}
	bool Type::IsArray()const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_array)))
		{
			return true;
		}
		return false;
	}
	bool type::IsClass()const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::Type_trait_infos::is_class)))
		{
			return true;
		}
		return false;
	}
	bool Type::IsEnum() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_enum)))
		{
			return true;
		}
		return false;
	}
	bool Type::IsFunctionPointer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_function_pointer)))
		{
			return true;
		}
		return false;
	}
	bool Type::IsMemberObjectPointer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_member_object_pointer)))
		{
			return true;
		}
		return false;
	}
	bool Type::IsMemberFunctionPointer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_member_function_pointer)))
		{
			return true;
		}
		return false;
	}
	bool Type::IsWrapped() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_wrappermapper)))
		{
			return true;
		}
		return false;
	}

	bool Type::IsSequentialContainer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_sequential_container)))
		{
			return true;
		}
		return false;
	}

	bool Type::IsAssociativeContainer() const noexcept
	{
		if (_data->_info.test(static_cast<size_t>(DETAIL::type_trait_infos::is_associative_container)))
		{
			return true;
		}
		return false;
	}
	DETAIL::type_data* Type::GetData()
	{
		return _data;
	}
	Type::Type()
		:_data(GetInvalidTypeData())
	{

	}
	Type::Type(DETAIL::type_data* data) :_data(data)
	{

	}
	Type GetInvalidType()
	{
		DETAIL::type_data* temp = DETAIL::GetInvalidTypeData();
		return Type(temp);
	}
}