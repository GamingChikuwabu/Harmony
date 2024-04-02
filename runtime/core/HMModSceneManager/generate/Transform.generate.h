#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_Transform \
private:\
friend struct G_Class_Declaration_Field_Transform;\
static HARMONY::Class* G_GetClassDataTransform();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataTransform();\
}\
inline virtual HARMONY::Class* GetClass()\
{\
return Transform::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_Transform