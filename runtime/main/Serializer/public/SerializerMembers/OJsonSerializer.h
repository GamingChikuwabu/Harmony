#pragma once
#include<ostream>
#include"HMString.h"

namespace HARMONY
{
	namespace SERIALIZER
	{
		class SERIALIZER_API OJsonSerializer
		{
		public:
			OJsonSerializer();
			~OJsonSerializer();
			template<typename T, typename Tp = std::remove_cvref_t<T>>
			HMString operator&(T&& obj);
		};
	}
}

#include"detail/OJsonSerializer_impl.h"