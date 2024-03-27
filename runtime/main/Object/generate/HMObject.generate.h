#pragma once
#include"Refrection.hpp"

template<>
static HARMONY::Class* GetStaticClass<class HARMONY::HMObject>();

static void AUTO_REGISTER_FUNCTION_HMObject();
struct AUTO_REGISTER_STRUCTURE_HMObject
{
	AUTO_REGISTER_STRUCTURE_HMObject() {
		AUTO_REGISTER_FUNCTION_HMObject();
	}
};



#define HM_GENARATE_BODY_HMObject \
public:
	static inline HARMONY::Class* StaticClass() {
		return GetStaticClass<class HARMONY::HMObject>();
	}



#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_HMObject