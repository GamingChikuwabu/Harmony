#pragma once
#include"gc/gc_cpp.h"
#include"HMString.h"
#include"ObjectMacro.h"
#include"Float3.h"
#include"HMObject.generate.h"

namespace HARMONY
{
	HMCLASS()
	class UTILITY_API HMObject : public  gc
	{
		HM_CLASS_BODY()
	public:
		HMObject();
		virtual ~HMObject();
		inline bool isValid()const noexcept;
	protected:
		HMPROPERTY()
		MATH::Float3 vec;
		HMPROPERTY()
		HMString _guid;
		HMPROPERTY()
		bool _isValid;
		HMPROPERTY()
		float ag;
		HMPROPERTY()
		int32_t test;
	};
}