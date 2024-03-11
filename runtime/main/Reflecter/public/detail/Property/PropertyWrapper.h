#pragma once

namespace HARMONY
{
	namespace DETAIL
	{
		enum class ACCESSLEVEL;
		template
		<
			typename ACCESSSTILE,
			typename GETTER,
			typename SETTER,
			ACCESSLEVEL ACC,
			typename GETPOLICY,
			typename SETPOLICY
		>
		class PropertyWrapper
		{

		};
	}
}

#include"PropertyWrapperMemberObject.inl"