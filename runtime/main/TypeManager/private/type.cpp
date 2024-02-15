#include"type.h"
#include"variant.h"


namespace HARMONY
{
	type::type()
	{

	}

	type type::getByName(std::string_view name)
	{
		return type();
	}

	variant type::Create()
	{
		return variant();
	}

	std::string_view type::GetName()
	{
		return std::string_view();
	}

	std::type_index type::GetTypeID()
	{
		return std::type_index();
	}

	std::size_t type::GetSizeof() const noexcept
	{
		return std::size_t();
	}

	type::operator bool() const noexcept
	{
	}

	type type::GetRawType() noexcept
	{
		return type();
	}

	type type::GetWrappedType() const noexcept
	{
		return type();
	}

	enumeration type::GetEnumeration() const
	{
		return enumeration();
	}

	constructor type::GetConstructor() const noexcept
	{
		return constructor();
	}

	std::vector<property> type::GetPropertys() noexcept
	{
		return std::vector<property>();
	}

	variant type::GetPropertyValue(std::string_view name, instance obj) noexcept
	{
		return variant();
	}

	bool type::SetPropertyValue(std::string_view name, instance obj) noexcept
	{
		return false;
	}

	bool type::isValid() noexcept
	{
		return false;
	}

	bool type::isArithmetic() noexcept
	{
		return false;
	}

	bool type::isEnumeration() noexcept
	{
		return false;
	}

	bool type::isArray() noexcept
	{
		return false;
	}

	bool type::isClass() noexcept
	{
		return false;
	}

	bool type::isWrapped() noexcept
	{
		return false;
	}

	bool type::isSequential() noexcept
	{
		return false;
	}

	bool type::isAssociation() noexcept
	{
		return false;
	}

	bool type::isPointer() noexcept
	{
		return false;
	}

	bool type::isFunctionPointer() noexcept
	{
		return false;
	}

	bool type::isMemberObjectPointer() noexcept
	{
		return false;
	}

	bool type::isMemberFunctionPointer() noexcept
	{
		return false;
	}

}