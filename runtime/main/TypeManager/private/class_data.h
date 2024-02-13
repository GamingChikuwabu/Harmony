#pragma once
#include"Types/type.h"
#include"Types/property.h"


namespace HARMONY
{
	namespace DETAIL
	{
		struct Class_Data
		{
			std::unordered_map<std::string, Property>                                       _properties;//プロパティのマップ
		};
	}
}