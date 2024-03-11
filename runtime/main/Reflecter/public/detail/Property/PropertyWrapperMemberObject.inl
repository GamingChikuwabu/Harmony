#include"PropertyWrapper.h"
#pragma once
#include"detail/Property/PropertyPolicy.h"
#include"detail/Property/PropertyWrapperBase.h"
#include"detail/AccessLevel.h"
#include"Value.h"

namespace HARMONY
{
	namespace DETAIL
	{
		template<typename C,typename A,ACCESSLEVEL acc> 
		class PropertyWrapper<member_object_ptr,A(C::*),void,acc,return_as_copy,set_value>
		:public DETAIL::PropertyWrapperBase
		{
			using access = A(C::*);
		public:
			PropertyWrapper(std::string name,access acc)
			:PropertyWrapper::PropertyWrapperBase(name)
			,_acc(acc)
			{
			}

			void SetValue(void* classInstance, Value value)override
			{
				C* _class = reinterpret_cast<C*>(classInstance); 
				A aval = value.TryConvert<A>();
				_class->*_acc = aval;
			};

			Value GetValue(void* classInstance)
			{
				C* _class = reinterpret_cast<C*>(classInstance);
				return Value(_class->*_acc);
			};
		private:
			access _acc;
		};
	}
}