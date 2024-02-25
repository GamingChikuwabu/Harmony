#pragma once
#include<string>
#include "type.h"
#include "variant"

namespace HARMONY
{
	namespace DETAIL
	{
		class instance;
		class property_wrapper_base
		{
		public:
			property_wrapper_base(std::string name, type declaring_type);
			~property_wrapper_base();
			type GetDeclaringType() const noexcept;
			const std::string& GetName() const noexcept;

		private:
			std::string _name;
			type		_type;
		};
	}
}