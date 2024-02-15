#include"property.h"
#include"variant.h"
#include"instance.h"

namespace HARMONY
{
	property::property(const property_data& data)
	{

	}
	property::property()
	{

	}
	variant property::GetValue(instance obj)
	{
		return variant();
	}
	void property::SetValue(instance obj, variant value)
	{
	}
	type property::GetType() const noexcept
	{
		return type();
	}
}