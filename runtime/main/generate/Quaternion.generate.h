#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_Quaternion \
private:\
friend struct G_Class_Declaration_Field_Quaternion;\
static HARMONY::Class* G_GetClassDataQuaternion();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataQuaternion();\
}\
inline virtual HARMONY::Class* GetClass()const\
{\
return Quaternion::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_Quaternion