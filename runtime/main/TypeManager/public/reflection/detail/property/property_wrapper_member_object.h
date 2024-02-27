#include"detail/property/property_wrapper.h"
#pragma once
#include"property_wrapper_base.h"
#include"detail/policy/prop_polisy.h"
#include"detail/type/access_type.h"
#include"access_level.h"

namespace HARMONY
{
	namespace DETAIL
	{
		template<typename C,typename A,access_level AccLevel>	
		class property_wrapper<member_object_ptr, A(C::*), void, AccLevel, return_as_copy, set_value>
			:public property_wrapper_base
		{
		public:
			using accessor = A(C::*);
			property_wrapper(std::string name,type dectype)
			:property_wrapper_base(name, dectype)
			{

			}
			type GetType()const noexcept
			{
				return type::Get<A>();
			}
			access_level GetAccessLevel()const noexcept
			{
				return AccLevel;
			}
			bool IsVaild()const noexcept { return true; }
			bool IsReadOnry()const noexcept { return false; }
			bool IsStatic()const noexcept { return false; }
			variant GetValue(variant obj)const noexcept
			{
				C* ret = obj.Convert<C*>();
				return variant(ret->*m_acc);
			}
			bool SetValue(variant obj, variant value)const noexcept
			{
				C* ret = obj.Convert<C*>();
				ret->*m_acc = value.Convert<A>();
				return false;
			}
		private:
			accessor m_acc;
		};
	}
}