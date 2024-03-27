#pragma once
#include<string>
#include"ObjectMacro.h"
#include"HMString.h"
#include"gc_cpp.h"
#include"HMObject.generate.h"

namespace HARMONY
{
	HMCLASS()
	class OBJECT_API HMObject : gc
	{
		HM_CLASS_BODY()
	public:
		HMObject();
		virtual ~HMObject();
	protected:
		HMPROPERTY()
		HMString _guid ;
	};
}