#pragma once
#include<string>
#include"GenerateMacro.h"
#include"HMString.h"

namespace HARMONY
{
	HMCLASS()
	class UTILITY_API HMObject
	{
		HM_CLASS_BODY()
	public:
		HMObject();
		virtual ~HMObject();
		int prop;
		HMString _guid ;
	protected:
		HMPROPERTY()
	};
}