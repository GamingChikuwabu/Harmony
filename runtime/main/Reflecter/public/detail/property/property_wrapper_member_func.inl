#pragma once
#include"Class/access_level.h"
#include"property_wrapper_base.h"
#include"policy/property_policy.h"
#include"policy/access_policy.h"

namespace HARMONY
{
	namespace DETAIL
	{
		template<typename C,typename A, ACCESS_LEVEL ACCLEVEL>
		class property_wrapper<member_object_pointer,A(C::*),void, ACCLEVEL,return_to_copy,set_value>
		:public property_wrapper_base
		{

		};
	}
}