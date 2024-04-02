#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_Component \
private:\
friend struct G_Class_Declaration_Field_Component;\
static HARMONY::Class* G_GetClassDataComponent();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataComponent();\
}\
inline virtual HARMONY::Class* GetClass()\
{\
return Component::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_Component