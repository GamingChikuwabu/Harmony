#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_Renderer \
private:\
friend struct G_Class_Declaration_Field_Renderer;\
static HARMONY::Class* G_GetClassDataRenderer();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataRenderer();\
}\
inline virtual HARMONY::Class* GetClass()\
{\
return Renderer::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_Renderer