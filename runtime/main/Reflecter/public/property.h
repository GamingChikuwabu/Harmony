#pragma once
#include<memory>
#include<string>
#include "Value.h"
namespace HARMONY
{
	namespace DETAIL
	{
		class PropertyWrapperBase;
	}
	class REFLECTER_API Property
	{
	public:
		~Property();
		std::string GetPropertyName();
		Value GetValue(void* classinstance);
		void SetValue(void* classinstance,Value value);
	private:
		Property() {};
		Property(std::shared_ptr<DETAIL::PropertyWrapperBase>);
		std::shared_ptr<DETAIL::PropertyWrapperBase> _wrapper;
		friend class Registration;
		friend class Class;
	};
}