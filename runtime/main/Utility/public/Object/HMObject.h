#pragma once
#include"Macro/ObjectMacro.h"
#include"HMString.h"
#include"gc/gc_cpp.h"
#include"Refrection.hpp"
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
		HMString _guid;
		HMPROPERTY()
		bool _isValid;
		HMPROPERTY()
		HMArray<int32_t> dummy;
	};
}