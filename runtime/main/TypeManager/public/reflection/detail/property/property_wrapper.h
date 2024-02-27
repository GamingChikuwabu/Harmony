#pragma once
#include"access_level.h"


namespace HARMONY
{
	namespace DETAIL
	{
		template<
			typename Accessor_Type, 
			typename Getter, 
			typename Setter, 
			access_level Acc_Level,
			typename Get_Policy, 
			typename Set_Policy>
		class property_wrapper;
	}
}