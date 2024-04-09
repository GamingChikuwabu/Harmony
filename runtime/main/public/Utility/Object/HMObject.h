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
		HMPROPERTY()
		HMUnorderedMap<uint32_t, HMString> _mapper;
	protected:
		HMPROPERTY()
		HMString _guid;
		HMPROPERTY()
		HMArray<MATH::Float3> _gg;
	};

	template<typename T, typename Enable = void>
	T* CreateObject() { return nullptr; }

	template<typename T,
		typename = std::enable_if_t<std::is_base_of_v<HMObject, T>,T>
	,typename ...Args>
	T* CreateObject(Args... args) {
		return new T(args); // Tのインスタンスを動的に生成して返す
	}
}