#pragma once
#include<string>
#include"Value.h"

namespace HARMONY
{
	namespace DETAIL
	{
		class PropertyWrapperBase
		{
		public:
			PropertyWrapperBase(std::string name)
			:_name(name) {}
			const std::string& GetPropertyName() { return _name; }
			
			virtual void SetValue(void* classInstance, Value value) {};

			virtual Value GetValue(void* classInstance) {};
		private:
			std::string _name;
		};
	}
}