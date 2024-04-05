#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_Float3 \
private:\
friend struct G_Class_Declaration_Field_Float3;\
static HARMONY::Class* G_GetClassDataFloat3();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataFloat3();\
}\
inline virtual HARMONY::Class* GetClass()const\
{\
return Float3::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_Float3