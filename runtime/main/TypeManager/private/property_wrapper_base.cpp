#include"detail/property/property_wrapper_base.h"

namespace HARMONY
{
	namespace DETAIL
	{
		property_wrapper_base::property_wrapper_base(std::string name, type declaring_type)
		:_name(name),_type(declaring_type)
		{

		}
		property_wrapper_base::~property_wrapper_base()
		{
		}
		type property_wrapper_base::GetDeclaringType() const noexcept
		{
			return _type;
		}
		const std::string& property_wrapper_base::GetName() const noexcept
		{
			return _name;
		}
		type property_wrapper_base::GetType() const noexcept
		{
			return GetInvalidType();
		}
		access_level property_wrapper_base::GetAccessLevel() const noexcept
		{
			return access_level::MAX;
		}
		bool property_wrapper_base::IsVaild()const noexcept
		{
			return false;
		}
		bool property_wrapper_base::IsReadOnry() const noexcept
		{
			return false;
		}
		bool property_wrapper_base::IsStatic()const noexcept
		{
			return false;
		}
		variant property_wrapper_base::GetValue(variant obj)const noexcept
		{
			return 0;
		}
		bool property_wrapper_base::SetValue(variant obj, variant value) const noexcept
		{
			return false;
		}
	}
}