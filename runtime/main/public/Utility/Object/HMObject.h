#pragma once
#include"gc/gc_cpp.h"
#include"HMString.h"
#include"HMArray.h"
#include"ObjectMacro.h"
#include"Float3.h"
#include"HMUnorderedMap.h"
#include"Macro/ManualRegisterMacro.h"
#include<utility>

namespace HARMONY
{
	class Class;
	HMCLASS()
	class UTILITY_API HMObject : public  gc
	{
		HM_MANUAL_REGISTER_BASE_CLASS_BODY(HMObject)
	public:
		HMObject();
		virtual ~HMObject();
		inline bool isValid()const noexcept;
	protected:
		HMPROPERTY()
		HMString _guid;
	};

	template<typename T,typename ...Args, typename Enable = void>
	T* CreateObject(Args&&... args)
	{
		return new (GC_NEW(T)) T(std::forward<Args>(args)...);
	}

	template<typename T,
	typename = std::enable_if_t<std::is_base_of_v<HMObject, T>,T>
	,typename ...Args>
	T* CreateObject(Args... args) {
		return new T(args); // Tのインスタンスを動的に生成して返す
	}
}