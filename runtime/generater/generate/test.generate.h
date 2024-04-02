#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_Vector3f \
private:\
friend struct G_Class_Declaration_Field_Vector3f;\
static HARMONY::Class* G_GetClassDataVector3f();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataVector3f();\
}\
inline virtual HARMONY::Class* GetClass()\
{\
return Vector3f::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_Vector3f