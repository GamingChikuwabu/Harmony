#pragma once
#define HM_GENARATE_BODY_HMObject\
private:\
friend struct G_Class_Declaration_Field_HMObject;\
static HARMONY::Class* G_GetClassDataHMObject();\
public:\
static inline HARMONY::Class* GetClass()\
{\
return G_GetClassDataHMObject();\
}\
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_HMObject