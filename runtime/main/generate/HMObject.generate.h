#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_HMObject \
private:\
friend struct G_Class_Declaration_Field_HMObject;\
static HARMONY::Class* G_GetClassDataHMObject();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataHMObject();\
}\
inline virtual HARMONY::Class* GetClass()const\
{\
return HMObject::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_HMObject