#pragma once
#define HM_GENARATE_BODY_ \
private:\
friend struct G_Class_Declaration_Field_;\
static HARMONY::Class* G_GetClassData();\
public:\
static inline HARMONY::Class* GetClass()\
{\
return G_GetClassData();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_