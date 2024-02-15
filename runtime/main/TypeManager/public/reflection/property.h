#pragma once
#include<memory>

namespace HARMONY
{
	struct property_data;
	class variant;
	class instance;
	class type;
	class property
	{
	public:
		variant GetValue(instance obj);
		void	SetValue(instance obj, variant value);
		type	GetType()const noexcept;
		property(const property_data& data);
		property();
	private:
		std::unique_ptr<property_data> _data;
	};
}