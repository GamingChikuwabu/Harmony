#pragma once
namespace HARMONY
{
	namespace DETAIL
	{
		enum class ACCESS_LEVEL;
		template<
			typename ACCESS_PLICY,
			typename GETTER,
			typename SETTER,
			ACCESS_LEVEL,
			typename GETPOLICY,
			typename SETPOLICY,
		>
		class property_wrapper{};
	}
}

#include"property_wrapper_member_func.inl"
#include"property_wrapper_member_object.inl"