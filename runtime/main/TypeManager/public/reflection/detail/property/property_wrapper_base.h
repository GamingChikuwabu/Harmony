#pragma once
#include<string>
#include "type.h"
#include "variant.h"
#include"access_level.h"

namespace HARMONY
{
	namespace DETAIL
	{
		class property_wrapper_base
		{
		public:
			property_wrapper_base(std::string name, type declaring_type);
			~property_wrapper_base();
			type GetDeclaringType() const noexcept;
			const std::string& GetName() const noexcept;
			virtual type GetType()const noexcept;
			virtual access_level GetAccessLevel()const noexcept;
			virtual bool IsVaild()const noexcept;
			virtual bool IsReadOnry()const noexcept;
			virtual bool IsStatic()const noexcept;
			virtual variant GetValue(variant obj)const noexcept;
			virtual bool    SetValue(variant obj,variant value)const noexcept;
		private:
			std::string _name;
			type		_type;
		};
	}
}