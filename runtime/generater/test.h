#pragma once
#include<string>
#include"ObjectMacro.h"
#include"HMString.h"
#include"gc/gc_cpp.h"
#include"Refrection.hpp"
#include"Utility.hpp"
#include"HMObject.generate.h"

namespace HARMONY
{
	HMCLASS()
	class OBJECT_API HMObject : public  gc
	{
		HM_CLASS_BODY()
	public:
		HMObject();
		virtual ~HMObject();
		inline bool isValid()const noexcept;
	protected:
		HMPROPERTY()
		HMString _guid;
		HMPROPERTY()
		bool _isValid;
	};
}