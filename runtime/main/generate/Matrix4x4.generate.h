#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_Matrix4x4 \
private:\
friend struct G_Class_Declaration_Field_Matrix4x4;\
static HARMONY::Class* G_GetClassDataMatrix4x4();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataMatrix4x4();\
}\
inline virtual HARMONY::Class* GetClass()const\
{\
return Matrix4x4::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_Matrix4x4