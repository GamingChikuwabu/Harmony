#include"property_wrapper_base.h"

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
	}
}