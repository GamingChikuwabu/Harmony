#pragma once
#include"Archive/access.h"
#include<string>
#include<typeinfo>
#include"Types/type.h"


namespace HARMONY
{
	namespace DETAIL
	{
		struct Property_Data
		{
			std::string _propertyName;
			Type        _propertyType; 
			PROPERTY_ACCESS_LEVEL _accessLevel;
		};
	}
}