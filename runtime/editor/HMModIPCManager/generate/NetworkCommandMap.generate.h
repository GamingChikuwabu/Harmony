#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_NetworkCommandMap \
private:\
friend struct G_Class_Declaration_Field_NetworkCommandMap;\
static HARMONY::Class* G_GetClassDataNetworkCommandMap();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataNetworkCommandMap();\
}\
inline virtual HARMONY::Class* GetClass()const\
{\
return NetworkCommandMap::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_NetworkCommandMap