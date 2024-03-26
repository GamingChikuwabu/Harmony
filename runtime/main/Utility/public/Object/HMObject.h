#pragma once
#include<string>
#include"GenerateMacro.h"
#include"HMString.h"
#include"HMArray.h"

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
		HMArray<int> _array;
	protected:
		HMPROPERTY()
	};
}