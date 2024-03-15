#pragma once
#include<string>
#include"GenerateMacro.h"

namespace HARMONY
{
	HMCLASS()
	class UTILITY_API HMObject
	{
		//HM_CLASS_BODY()
	public:
		HMObject();
		virtual ~HMObject();
		std::string _guid;
	protected:
		HMPROPERTY()
	};
};