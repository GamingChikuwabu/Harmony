#include"Property.h"
#include"Property/PropertyWrapperBase.h"

namespace HARMONY
{
	Property::Property(std::shared_ptr<DETAIL::PropertyWrapperBase> wrapper)
	:_wrapper(wrapper)
	{
		
	}

	Property::~Property()
	{
		
	}
	std::string Property::GetPropertyName()
	{
		return _wrapper->GetPropertyName();
	}
	Value Property::GetValue(void* classInstance)
	{
		return _wrapper->GetValue(classInstance);
	}
	void Property::SetValue(void* classInstance, Value value)
	{
		return _wrapper->SetValue(classInstance, value);
	}
}