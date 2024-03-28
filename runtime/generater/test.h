#pragma once
#include<string>
#include"GenerateMacro.h"

namespace HARMONY
{
	namespace TEST
	{
	HMCLASS()
    class damy;
	template<class T>
	class UTILITY_API HMObject
	{
		HM_CLASS_BODY()
	public:
		HMObject();
		virtual ~HMObject();
	protected:
        HMPROPERTY(COMMENT:"fのコメント")
        int32_t f = 0;
        std::uniq_ptr<int> ptr;
	};
	}
};