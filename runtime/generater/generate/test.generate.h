#pragma once
namespace HARMONY{class Class;}
#define HM_GENARATE_BODY_CommandInfo \
private:\
friend struct G_Class_Declaration_Field_CommandInfo;\
static HARMONY::Class* G_GetClassDataCommandInfo();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
return G_GetClassDataCommandInfo();\
}\
inline virtual HARMONY::Class* GetClass()const\
{\
return CommandInfo::StaticGetClass();\
}
#undef _GENARATED
#define _GENARATED  HM_GENARATE_BODY_CommandInfo