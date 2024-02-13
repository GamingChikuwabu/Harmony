#pragma once
#include<type_traits>
#include"Types/property.h"
#include"property_data.h"
#include"Types/type.h"

namespace HARMONY
{
	namespace DETAIL
	{
		class ItemCreater
		{
		public:
			template<typename T,typename TYPE>
			static std::enable_if_t<std::is_same<Property, T>::value, void>
			CreateProperty(Property& prop,std::string name,size_t size) { 
				prop._data->init<TYPE>(name,size);
			};
		private:


		};
		
	}
}