#pragma once
#define HM_GENARATE_BODY_GameObject \
private:\
friend struct G_Class_Declaration_Field_GameObject;\
static HARMONY::Class* G_GetClassDataGameObject();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataGameObject();\
}\
inline virtual HARMONY::Class* GetClass()\
{\
return GameObject::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_GameObject