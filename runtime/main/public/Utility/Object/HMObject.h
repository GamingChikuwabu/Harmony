#pragma once
#include"gc/gc_cpp.h"
#include"HMString.h"
#include"HMArray.h"
#include"ObjectMacro.h"
#include"Float3.h"
#include"HMUnorderedMap.h"
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
		HMArray<MATH::Float3> _gg;
		HMPROPERTY()
		HMUnorderedMap<uint32_t, HMString> _mapper;
	};
}