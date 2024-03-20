#pragma once
#include<string>
#include<rttr/type>

namespace HARMONY
{
	namespace SERIALIZE
	{
		namespace JSON
		{
			class SERIALIZER_API OJsonSerializer
			{
			public:
				OJsonSerializer();
				std::string operator<<(rttr::instance instance);
			};
		}
	}
}