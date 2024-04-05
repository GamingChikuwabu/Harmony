#pragma once
#include"gc/gc_cpp.h"
#include"HMString.h"
#include"ObjectMacro.h"
#include"Vector3f.h"
#include"HMObject.generate.h"

namespace HARMONY
{
	HMCLASS()
	class UTILITY_API HMObject : public  gc
	{
	private:friend struct G_Class_Declaration_Field_HMObject; static HARMONY::Class* G_GetClassDataHMObject(); public:static inline HARMONY::Class* StaticGetClass() {
		return G_GetClassDataHMObject();
	}inline virtual HARMONY::Class* GetClass()const {
		return HMObject::StaticGetClass();
	}
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
		MATH::Vector3f vec;
		HMPROPERTY()
		float ag;
		HMPROPERTY()
		int32_t test;
	};
}