#pragma once
#include<string>
#include<rttr/type>

namespace HARMONY
{
	namespace SERIALIZE
	{
		namespace JSON
		{
			class SERIALIZER_API IJsonSerializer
			{
			public:
				IJsonSerializer(const std::string json);
				void operator>>(rttr::instance obj);	
			};
		}
	}
}